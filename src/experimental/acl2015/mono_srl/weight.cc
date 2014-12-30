#include "experimental/acl2015/mono_srl/weight.h"
#include "experimental/acl2015/mono_srl/action.h"
#include "experimental/acl2015/mono_srl/score_context.h"

namespace ZuoPar {
namespace Experimental {
namespace ACL2015 {
namespace MonoSRL {

Weight::Weight() {
  ZUOPAR_FEATURE_MAP_REGIST_U1( w_2 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w_1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w0 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w2 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_2 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p0 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p2 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w_2, w_1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w_1, w0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w0, w1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w1, w2 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( p_2, p_1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( p_1, p0 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( p0, p1 );
  ZUOPAR_FEATURE_MAP_REGIST_B11( p1, p2 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( w_pred );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_pred );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_pred_1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( p_pred1 );
  ZUOPAR_FEATURE_MAP_REGIST_U1( position );
  ZUOPAR_FEATURE_MAP_REGIST_U1( dist );
  ZUOPAR_FEATURE_MAP_REGIST_B11( w0, w_pred );
  ZUOPAR_FEATURE_MAP_REGIST_B11( position, w_pred );
  ZUOPAR_FEATURE_MAP_REGIST_B11( position, w0 );
  ZUOPAR_FEATURE_MAP_REGIST_T111( position, w0, w_pred );
  ZUOPAR_FEATURE_MAP_REGIST_B11( position, vc_pred );
  ZUOPAR_FEATURE_MAP_REGIST_T111( position, w0, vc_pred );
  ZUOPAR_FEATURE_MAP_REGIST_B11( position, p_pred );
  ZUOPAR_FEATURE_MAP_REGIST_B11( position, p0 );
  ZUOPAR_FEATURE_MAP_REGIST_T111( position, p0, w_pred );
  ZUOPAR_FEATURE_MAP_REGIST_B11( position, vc_pred );
  ZUOPAR_FEATURE_MAP_REGIST_T111( position, p0, vc_pred );
}

} //  namespace monosrl
} //  namespace acl2015
} //  namespace experimental
} //  namespace zuopar