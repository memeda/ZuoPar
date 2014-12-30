#ifndef __ZUOPAR_APP_LEXANALYZER_POSTAGGER_OPT_H__
#define __ZUOPAR_APP_LEXANALYZER_POSTAGGER_OPT_H__

#include <iostream>

namespace ZuoPar {
namespace LexicalAnalyzer {
namespace Postagger {

struct Option {
  std::string model_path; //! The path to the model file.
  bool conll_format;      //! The input file is in CoNLL format.
  int beam_size;          //! The size of the beam.
  int display_interval;   //! The interval for displaying log.
};

struct LearnOption: public Option {
  std::string reference_path; //! The path to the reference file.
};

struct TestOption: public Option {
  std::string input_path;     //! The path to the input file.
  std::string output_path;    //! The path to the output file.
};

}
}
}

#endif  //  end for __ZUOPAR_APP_LEXANALYZER_POSTAGGER_OPT_H__