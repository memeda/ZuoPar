#include <iostream>
#include <cstring>  // strcmp
#include "utils/logging.h"
#include "experimental/acl2015/mono_predicate_srl/opt.h"
#include "experimental/acl2015/mono_predicate_srl/opt_utils.h"
#include "experimental/acl2015/mono_predicate_srl/pipe.h"

namespace po = boost::program_options;
namespace fe = ZuoPar::FrontEnd;
namespace mono = ZuoPar::Experimental::ACL2015::MonoPredicateSRL;

int multi_learn(int argc, char** argv) {
  /*std::string usage = "Multi-threaded training component of ZuoPar::sequence labeler.\n";
  usage += "Author: Yijia Liu (oneplus.lau@gmail.com).\n\n";
  usage += "Usage: sequence_labeler multi-learn [options]\n";
  usage += "OPTIONS";

  po::options_description optparser = fe::build_multi_learn_optparser(usage);

  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);

  fe::MultiLearnOption opts;
  if (!parse_multi_learn_option_ext(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  //mono::MultiPipe pipe(opts);
  //pipe.run(); */
  return 1;
}

/**
 * Perform the learning process of ZuoPar::arcstandard dependency parser.
 *
 *  @param[in]  argc  The number of arguments.
 *  @param[in]  argv  The arguments.
 *  @return     int   The status of running learning.
 */
int learn(int argc, char** argv) {

  std::string usage = "Training component of ZuoPar::acl2015(semantic role labeler).\n";
  usage += "Author: Yijia Liu (oneplus.lau@gmail.com).\n\n";
  usage += "Usage: acl2015 learn [options]\n";
  usage += "OPTIONS";

  po::options_description optparser = fe::build_learn_optparser(usage);
  optparser.add_options()("verb-class", po::value<std::string>(), "The path to the verb class.");
  optparser.add_options()("predicate", po::value<std::string>(), "The predicate tag.");

  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);

  mono::LearnOption opts;
  if (!mono::parse_learn_option_ext(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  mono::Pipe pipe(opts);
  pipe.run();
  return 0;
}

/**
 * Perform the testing process of ZuoPar::arcstandard dependency parser.
 *
 *  @param[in]  argc  The number of arguments.
 *  @param[in]  argv  The arguments.
 *  @return     int   The status of running test.
 */
int test(int argc, char** argv) {
  std::string usage = "Testing component of ZuoPar::acl2015(semantic role labeler).\n";
  usage += "Author: Yijia Liu (oneplus.lau@gmail.com).\n\n";
  usage += "Usage: sequence_labeler test [options]\n";
  usage += "OPTIONS";

  po::options_description optparser = fe::build_test_optparser(usage);
  optparser.add_options()
    ("verb-class", po::value<std::string>(), "The path to the verb class.")
    ("predicate", po::value<std::string>(), "The predicate tag.")
    ("format", po::value<std::string>(), "The output format\n"
                                         " - semchunk: the semantic chunk [default]\n"
                                         " - conll: the conll props.");


  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);

  mono::TestOption opts;
  if (!mono::parse_test_option_ext(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }
  mono::Pipe pipe(opts);
  pipe.run();

  return 0;
}

#include "frontend/template/main.h"
MAIN("Semantic Role Labeler with Mono Predicate", "experimental/mono_predicate_srl")