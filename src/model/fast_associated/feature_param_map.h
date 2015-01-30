#ifndef __ZUOPAR_MODEL_FAST_ASSOCIATED_FEATURE_PARAM_MAP_H__
#define __ZUOPAR_MODEL_FAST_ASSOCIATED_FEATURE_PARAM_MAP_H__

#include "settings.h"
#include "types/math/sparse_vector.h"
#include "types/internal/packed_scores.h"
#include "ml/pointwise_param.h"
#include "model/feature.h"
#include "utils/logging.h"
#include <boost/functional/hash.hpp>

#if defined(UNORDERED_MAP_IMPL) && (UNORDERED_MAP_IMPL == dense_hash_map)
# include <google/dense_hash_map>
# include "utils/serialization/dense_hash_map.h"
#else
# include <unordered_map>
# include "utils/serialization/unordered_map.h"
# warning ("use std::unordered_map which is slow")
#endif

namespace ZuoPar {

/**
 * FeaturePointwiseParamMap is the class use to store the model parameters 
 * of the feature. One FeaturePointwiseParamMap maintains several Features.
 * These features are extracted from the same feature template.
 *
 * Map [ ActionFeature ] = Parameter
 */
template <
  class _MetaFeatureType,
  class _ScoreContextType,
  class _ActionType
>
class FeatureParameterMap {
private:
  //! Define the feature type.
  typedef Feature<_MetaFeatureType, _ActionType> feature_t;

  //! Define the parameter type.
  typedef MachineLearning::PointwiseParameter param_t;

  //! Define the mapping type.
#if defined(UNORDERED_MAP_IMPL) && (UNORDERED_MAP_IMPL == dense_hash_map)
  typedef google::dense_hash_map<
    feature_t,
    param_t,
    boost::hash<feature_t>
  > map_t;
#else
  typedef std::unordered_map<
    feature_t,
    param_t,
    boost::hash<feature_t>
  > map_t;
#endif

  //! Define the cache type.
  typedef std::vector<_MetaFeatureType> cache_t;

  //! Define the functor type.
  typedef std::function<void(const _ScoreContextType&, cache_t&)> extractor_t;

  //! Define the packed score type.
  typedef PackedScores<_ActionType> packed_score_t;
public:
  /**
   * The constructor
   *
   *  @param[in]  extractor_  The extraction functor.
   */
  FeatureParameterMap(extractor_t extractor_)
    : extractor(extractor_) {
#if defined(UNORDERED_MAP_IMPL) and (UNORDERED_MAP_IMPL == dense_hash_map)
    payload.set_empty_key(feature_t());
#endif
  }

  /**
   * Convert the pointwised feature into vector.
   *
   *  @param[in]  ctx           The score context
   *  @param[in]  act           The action
   *  @param[in]  scale         Increase the value in sparse_vector by scale.
   *  @param[in]  offset        The offset for counting vector.
   *  @param[out] sparse_vector The sparse vector.
   */
  void vectorize(const _ScoreContextType& ctx, const _ActionType& act,
      floatval_t scale, int offset, SparseVector* sparse_vector) {
    //! Use to cache extracted features.
    cache_t cache;
    extractor(ctx, cache);
    for (const _MetaFeatureType& c: cache) {
      const feature_t& entry = feature_t(c, act);
      int id = offset;
      for (typename map_t::const_iterator itx = payload.begin();
          itx != payload.end();
          ++ itx, ++ id) {
        if (itx->first == entry) {
          (*sparse_vector)[id] += scale;
          break;
        }
      }
    }
  }

  /**
   * Convert the pointwised feature into sparse vector2 (a faster version of
   * representing sparse vector).
   *
   *  @param[in]  ctx           The score context
   *  @param[in]  act           The action
   *  @param[in]  scale         Specify to use averaged parameter.
   *  @param[in]  gid           The offset for counting vector.
   *  @param[out] sparse_vector The sparse vector.
   */
  void vectorize2(const _ScoreContextType& ctx, const _ActionType& act,
      floatval_t scale, int gid, SparseVector2* sparse_vector) {
    cache_t cache;
    extractor(ctx, cache);
    for (const _MetaFeatureType& c: cache) {
      const feature_t& entry = feature_t(c, act);
      typename map_t::const_iterator itx = payload.find(entry);
      if (itx == payload.end()) {
        continue;
      }

      const std::pair<int, std::size_t>& key =
        std::make_pair(gid, boost::hash_value<feature_t>(entry));
      (*sparse_vector)[key] += scale;
    }
  }

  //! The size of the feature parameter map.
  std::size_t size() const {
    return payload.size();
  }

  /**
   * Get the score for the (context, action) pair
   *
   *  @param[in]  ctx   The scoring context.
   *  @param[in]  act   The action.
   *  @param[in]  avg   If avg is true return the averaged parameter, else
   *                    return the non-averaged parameter.
   *  @param[in]  default_return_value  The default return value.
   *  @return     floatval_t  The score.
   */
  floatval_t score(const _ScoreContextType& ctx, const _ActionType& act,
      bool avg, floatval_t default_return_value = 0.) {
    cache_t cache;
    extractor(ctx, cache);
    floatval_t ret = 0.;
    for (const _MetaFeatureType& c: cache) {
      const feature_t& entry = feature_t(c, act);

      typename map_t::const_iterator itx = payload.find(entry);
      if (itx != payload.end()) {
        if (avg) {
          ret += itx->second.w_sum;
        } else {
          ret += itx->second.w;
        }
      }
    }
    return ret;
  }

  /**
   * Batchly calculate the scores.
   *
   *  @param[in]  ctx     The scoring context.
   *  @param[in]  actions The actions.
   *  @param[in]  avg     If avg is true return the averaged parameter, else
   *                      return the non-averaged parameter.
   *  @param[out] result  The return value.
   */
  void batchly_score(const _ScoreContextType& ctx,
      const std::vector<_ActionType>& actions,
      bool avg,
      packed_score_t& result) {
    cache_t cache;
    extractor(ctx, cache);
    for (const _MetaFeatureType& c: cache) {
      feature_t entry(c, actions[0]);
      for (const _ActionType& act: actions) {
        entry.replace_action(act);

        typename map_t::const_iterator itx = payload.find(entry);
        if (itx == payload.end()) {
          continue;
        }
        if (avg) {
          result[act] += itx->second.w_sum;
        } else {
          result[act] += itx->second.w;
        }
      }
    }
  }

  /**
   * Update the parameter for the (context, action) pair
   *
   *  @param[in]  ctx   The scoring context.
   *  @param[in]  act   The action
   *  @param[in]  now   The current timestamp.
   *  @param[in]  scale The updated scale.
   */
  void update(const _ScoreContextType& ctx, const _ActionType& act,
      int now, floatval_t scale = 1.) {
    cache_t cache;
    extractor(ctx, cache);
    for (const _MetaFeatureType& c: cache) {
      const feature_t& entry = feature_t(c, act);
      param_t& param = payload[entry];
      param.add(now, scale);
    }
  }

  /**
   * Flush the last updated time for all the parameters.
   *
   *  @param[in]  now   The timestamp.
   */
  void flush(int now) {
    for (typename map_t::iterator itx = payload.begin();
        itx != payload.end(); ++ itx) {
      itx->second.flush(now);
    }
  }

  /**
   * Saving the score map to the archive.
   *
   *  @param[in]  oa    The output archive stream.
   */
  void save(boost::archive::text_oarchive& oa) {
    oa << payload;
  }

  /**
   * Loading the score map from the archive.
   *
   *  @param[in] ia   The input archive stream.
   */
  void load(boost::archive::text_iarchive& ia) {
    ia >> payload;
  }

private:
  //! The mapping facility.
  map_t payload;

  //! The feature extracting functor.
  extractor_t extractor;
};

} //  namespace zuopar

#endif  //  end for __ZUOPAR_MODEL_FAST_ASSOCIATED_FEATURE_PARAM_MAP_H__
