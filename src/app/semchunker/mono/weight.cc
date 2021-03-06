#include "app/semchunker/mono/weight.h"
#include "app/semchunker/mono/action.h"
#include "app/semchunker/mono/score_context.h"

namespace ZuoPar {
namespace SemanticChunker {
namespace MonoPredicate {

Weight::Weight() {
  ZUOPAR_FEATURE_MAP_REGIST_U1( w_2 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w_1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w0 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w2 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w_2, w_1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w_1, w0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w0, w1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w1, w2 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w_pred );
  ZUOPAR_FEATURE_MAP_REGIST_U1( position );
  ZUOPAR_FEATURE_MAP_REGIST_U1( dist );
  ZUOPAR_FEATURE_MAP_REGIST_U1( vc_pred );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w0, w_pred );
  ZUOPAR_FEATURE_MAP_REGIST_B00( vc_pred, position );
  ZUOPAR_FEATURE_MAP_REGIST_B10( w_pred, position );
  ZUOPAR_FEATURE_MAP_REGIST_B10( w0, position );
  ZUOPAR_FEATURE_MAP_REGIST_T110( w0, w_pred, position );
  ZUOPAR_FEATURE_MAP_REGIST_T100( w0, vc_pred, position );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_2 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p0 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p2 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( p_2, p_1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( p_1, p0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( p0, p1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( p1, p2 );
  ZUOPAR_FEATURE_MAP_REGIST_S0( path );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_pred );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_pred_1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_pred1 );
  ZUOPAR_FEATURE_MAP_REGIST_B10( p_pred, position );
  ZUOPAR_FEATURE_MAP_REGIST_B10( p0, position );
  ZUOPAR_FEATURE_MAP_REGIST_T110( p0, p_pred, position );
  ZUOPAR_FEATURE_MAP_REGIST_T100( p0, vc_pred, position);
  ZUOPAR_FEATURE_MAP_REGIST_U1( t_1 );
  ZUOPAR_FEATURE_MAP_REGIST_T110( w0, w_pred, label_set );
  ZUOPAR_FEATURE_MAP_REGIST_T110( p0, p_pred, label_set );
}

} //  namespace monopredicate
} //  namespace semanticchunker
} //  namespace zuopar
