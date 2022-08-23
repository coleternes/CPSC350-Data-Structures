#include <iostream>
#include <fstream>

using namespace std;

class NucleoReader {
  private:
    //The current line of the file
    string m_line;

    //All of the statistics associated with the file
    int m_line_sum;
    int m_num_of_lines;
    float m_mean;
    float m_var;
    float m_std_dev;

    //Individual nucleotide probabilities
    int m_a_counter;
    int m_t_counter;
    int m_c_counter;
    int m_g_counter;
    float m_a_prob;
    float m_t_prob;
    float m_c_prob;
    float m_g_prob;

    //Nucleotide bigram probabilities
    int m_aa_counter;
    int m_at_counter;
    int m_ac_counter;
    int m_ag_counter;
    int m_ta_counter;
    int m_tt_counter;
    int m_tc_counter;
    int m_tg_counter;
    int m_ca_counter;
    int m_ct_counter;
    int m_cc_counter;
    int m_cg_counter;
    int m_ga_counter;
    int m_gt_counter;
    int m_gc_counter;
    int m_gg_counter;
    float m_aa_prob;
    float m_at_prob;
    float m_ac_prob;
    float m_ag_prob;
    float m_ta_prob;
    float m_tt_prob;
    float m_tc_prob;
    float m_tg_prob;
    float m_ca_prob;
    float m_ct_prob;
    float m_cc_prob;
    float m_cg_prob;
    float m_ga_prob;
    float m_gt_prob;
    float m_gc_prob;
    float m_gg_prob;

    //The total number of bigrams in a file
    int m_double_line_sum;
  public:
    NucleoReader();
    ~NucleoReader();
    /*
    * Part 1: Finding Values
    * The following function signatures are where the first part of the
    * program take place. This includes finding the sum, mean, variance,
    * standard deviation, individual nucleotide probability, and every
    * combo of nucleotide bigram probability.
    */
    void calcSum(string fileName);
    void calcMean();
    void calcVar(string fileName);
    void calcStdDev();
    void calcNucleoProb(string fileName);
    void calcNucleoBigramProb(string fileName);
    /*
    * Part 2: Recreating Appropriate DNA
    * Printing out 1000 lines of DNA that fit the criteria
    * - Use the calculations provided in the hint to generate each line's length
    * - Use the individual nucleotide probabilities to generate how the lines are filled
    */
    void printSampleFile();
};
