#ifndef __ZUOPAR_UTILS_IO_DATASET_SEMANTIC_CHUNKS_H__
#define __ZUOPAR_UTILS_IO_DATASET_SEMANTIC_CHUNKS_H__

#include <iostream>
#include <vector>
#include "types/semchunks.h"
#include "utils/io/instance/semchunks.h"
#include "engine/token_alphabet.h"

namespace ZuoPar {
namespace IO {

namespace eg = ZuoPar::Engine;

/**
 * Read dependency dataset. In each instance, one item per line. For each item,
 * there are 4 column representing: form, postag, blank, senses, apreds. Instances
 * are separated by newline.
 *
 *  @param[in]  is                The input stream.
 *  @param[out] dataset           The output dataset.
 *  @param[out] forms_alphabet    The alphabet for forms.
 *  @param[out] postags_alphabet  The alphabet for postags.
 *  @param[out] senses_alphabet   The alphabet for senses.
 *  @param[out] chunks_alphabet   The alphabet for chunk tag.
 *  @param[in]  predicate_tag     The tag of predicate.
 *  @param[in]  incremental       If incremental is true, insert the token into
 *                                the alphabet, otherwise not perform insertion.
 */
void read_semchunks_dataset(
    std::istream& is,
    std::vector<SemanticChunks>& dataset,
    eg::TokenAlphabet& forms_alphabet,
    eg::TokenAlphabet& postags_alphabet,
    eg::TokenAlphabet& senses_alphabet,
    eg::TokenAlphabet& chunks_alphabet,
    const std::string& predicate_tag = "V",
    bool incremental = true);

} // namespace io
} // namespace zuopar

#endif  //  end for __ZUOPAR_UTILS_IO_DATASET_SEMANTIC_CHUNKS_H__
