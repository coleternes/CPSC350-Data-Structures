#include "NucleoReader.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

NucleoReader::NucleoReader() {
  //The current line of the file
  m_line = "";

  //All of the statistics associated with the file
  m_line_sum = 0;
  m_num_of_lines = 0;
  m_mean = 0.0f;
  m_var = 0.0f;
  m_std_dev = 0.0f;

  //Individual nucleotide probabilities
  m_a_counter = 0;
  m_t_counter = 0;
  m_c_counter = 0;
  m_g_counter = 0;
  m_a_prob = 0.0f;
  m_t_prob = 0.0f;
  m_c_prob = 0.0f;
  m_g_prob = 0.0f;

  //Nucleotide bigram probabilities
  m_aa_counter = 0;
  m_at_counter = 0;
  m_ac_counter = 0;
  m_ag_counter = 0;
  m_ta_counter = 0;
  m_tt_counter = 0;
  m_tc_counter = 0;
  m_tg_counter = 0;
  m_ca_counter = 0;
  m_ct_counter = 0;
  m_cc_counter = 0;
  m_cg_counter = 0;
  m_ga_counter = 0;
  m_gt_counter = 0;
  m_gc_counter = 0;
  m_gg_counter = 0;
  m_aa_prob = 0.0f;
  m_at_prob = 0.0f;
  m_ac_prob = 0.0f;
  m_ag_prob = 0.0f;
  m_ta_prob = 0.0f;
  m_tt_prob = 0.0f;
  m_tc_prob = 0.0f;
  m_tg_prob = 0.0f;
  m_ca_prob = 0.0f;
  m_ct_prob = 0.0f;
  m_cc_prob = 0.0f;
  m_cg_prob = 0.0f;
  m_ga_prob = 0.0f;
  m_gt_prob = 0.0f;
  m_gc_prob = 0.0f;
  m_gg_prob = 0.0f;

  //The total number of bigrams in a file
  m_double_line_sum = 0;
}

NucleoReader::~NucleoReader() { }

//Calculates and writes out the sum
void NucleoReader::calcSum(string fileName) {
  //Opens a file with the name given in argv
  ifstream currentFile (fileName + ".txt");

  //Checks to see if the file is currently open
  if (currentFile.is_open()) {
    //Reads through the file and sums up length of lines and counts num of lines
    while (getline(currentFile, m_line)) {
      m_line_sum += m_line.size();
      m_num_of_lines++;
    }
    //Closes the file
    currentFile.close();
    //Prints out the sum
    cout << "Sum: " << m_line_sum << endl;
  } else {
    cout << "ERROR: Cannot open file." << endl;
  }
}

//Calculates and writes out the mean
void NucleoReader::calcMean() {
  m_mean = (float) m_line_sum / (float) m_num_of_lines;

  cout << "Mean: " << m_mean << endl;
}

//Calculates and writes out the variance
void NucleoReader::calcVar(string fileName) {
  //Opens a file with the name given in argv
  ifstream currentFile (fileName + ".txt");

  //Initializes and declares the value
  float totalSquare = 0;

  //Checks to see if the file is currently open
  if (currentFile.is_open()) {
    //Reads through the file and calculates the sum of all squares for the variance
    while (getline(currentFile, m_line)) {
      int currentLineLength = m_line.size();
      float currentSquare = (currentLineLength - m_mean) * (currentLineLength - m_mean);
      totalSquare += currentSquare;
    }
    //Closes the file
    currentFile.close();
    //Calculates the variance
    m_var = totalSquare / (float) m_num_of_lines;
    //Writes out the variance
    cout << "Variance: " << m_var << endl;
  } else {
    cout << "ERROR: Cannot open file." << endl;
  }
}

//Calculates and writes out the standard deviation
void NucleoReader::calcStdDev() {
  m_std_dev = sqrt(m_var);

  cout << "Standard Deviation: " << m_std_dev << endl;
}

//Calculates each nucleotide's probability of occuring in the file and writes it out
void NucleoReader::calcNucleoProb(string fileName) {
  //Opens a file with the name given in argv
  ifstream currentFile (fileName + ".txt");

  //Checks to see if the file is currently open
  if (currentFile.is_open()) {
    //Goes through each line in the file
    while (getline(currentFile, m_line)) {
      //Checks each char in the current string and increases the appropriate counter
      for (int i = 0; i < m_line.size(); ++i) {
        char currentChar = tolower(m_line[i]);
        if (currentChar == 'a')
          ++m_a_counter;
        else if (currentChar == 't')
          ++m_t_counter;
        else if (currentChar == 'c')
          ++m_c_counter;
        else if (currentChar == 'g')
          ++m_g_counter;
      }
    }
    //Closes the file
    currentFile.close();
    //Calculates each nucleotide's probability
    m_a_prob = (float) m_a_counter / (float) m_line_sum;
    m_t_prob = (float) m_t_counter / (float) m_line_sum;
    m_c_prob = (float) m_c_counter / (float) m_line_sum;
    m_g_prob = (float) m_g_counter / (float) m_line_sum;
    //Writes out each nucleotide's probability
    cout << "Probability of A: " << m_a_prob << endl;
    cout << "Probability of T: " << m_t_prob << endl;
    cout << "Probability of C: " << m_c_prob << endl;
    cout << "Probability of G: " << m_g_prob << endl;
  } else {
    cout << "ERROR: Cannot open file." << endl;
  }
}

//Calculates each nucleotide bigram's probability of occuring in the file and writes it out
void NucleoReader::calcNucleoBigramProb(string fileName) {
  //Opens a file with the name given in argv
  ifstream currentFile (fileName + ".txt");

  //Initializes and declares the values used to iterate through the line
  int i = 0;
  int j = 1;

  //Checks to see if the file is currently open
  if (currentFile.is_open()) {
    //Goes through each line in the file
    while (getline(currentFile, m_line)) {
      m_double_line_sum += m_line.size();
      //Checks each sequential bigram found in the current line and
      //increases appropriate counter
      while (i < m_line.size() && j < m_line.size()) {
        //The first and second char of the bigram
        char firstChar = tolower(m_line[i]);
        char secondChar = tolower(m_line[j]);
        if (firstChar == 'a' && secondChar == 'a')
          m_aa_counter++;
        else if (firstChar == 'a' && secondChar == 't')
          m_at_counter++;
        else if (firstChar == 'a' && secondChar == 'c')
          m_ac_counter++;
        else if (firstChar == 'a' && secondChar == 'g')
          m_ag_counter++;
        else if (firstChar == 't' && secondChar == 'a')
          m_ta_counter++;
        else if (firstChar == 't' && secondChar == 't')
          m_tt_counter++;
        else if (firstChar == 't' && secondChar == 'c')
          m_tc_counter++;
        else if (firstChar == 't' && secondChar == 'g')
          m_tg_counter++;
        else if (firstChar == 'c' && secondChar == 'a')
          m_ca_counter++;
        else if (firstChar == 'c' && secondChar == 't')
          m_ct_counter++;
        else if (firstChar == 'c' && secondChar == 'c')
          m_cc_counter++;
        else if (firstChar == 'c' && secondChar == 'g')
          m_cg_counter++;
        else if (firstChar == 'g' && secondChar == 'a')
          m_ga_counter++;
        else if (firstChar == 'g' && secondChar == 't')
          m_gt_counter++;
        else if (firstChar == 'g' && secondChar == 'c')
          m_gc_counter++;
        else if (firstChar == 'g' && secondChar == 'g')
          m_gg_counter++;
        //Appropriately increases the values used to iterate through the line
        i += 2;
        j += 2;
      }
      //If the current line is an odd length, then we dont count the last char
      if (m_double_line_sum % 2 == 1)
        m_double_line_sum--;
      //Resets the values used to iterate once at the end of the current line
      i = 0;
      j = 1;
    }
    //Closes the file
    currentFile.close();
    //Calculates each nucleotide bigram's probability
    m_aa_prob = (float) m_aa_counter / (float) (m_double_line_sum / 2.0);
    m_at_prob = (float) m_at_counter / (float) (m_double_line_sum / 2.0);
    m_ac_prob = (float) m_ac_counter / (float) (m_double_line_sum / 2.0);
    m_ag_prob = (float) m_ag_counter / (float) (m_double_line_sum / 2.0);
    m_ta_prob = (float) m_ta_counter / (float) (m_double_line_sum / 2.0);
    m_tt_prob = (float) m_tt_counter / (float) (m_double_line_sum / 2.0);
    m_tc_prob = (float) m_tc_counter / (float) (m_double_line_sum / 2.0);
    m_tg_prob = (float) m_tg_counter / (float) (m_double_line_sum / 2.0);
    m_ca_prob = (float) m_ca_counter / (float) (m_double_line_sum / 2.0);
    m_ct_prob = (float) m_ct_counter / (float) (m_double_line_sum / 2.0);
    m_cc_prob = (float) m_cc_counter / (float) (m_double_line_sum / 2.0);
    m_cg_prob = (float) m_cg_counter / (float) (m_double_line_sum / 2.0);
    m_ga_prob = (float) m_ga_counter / (float) (m_double_line_sum / 2.0);
    m_gt_prob = (float) m_gt_counter / (float) (m_double_line_sum / 2.0);
    m_gc_prob = (float) m_gc_counter / (float) (m_double_line_sum / 2.0);
    m_gg_prob = (float) m_gg_counter / (float) (m_double_line_sum / 2.0);
    //Writes out each nucleotide bigram's probability
    cout << "Probability of AA: " << m_aa_prob << endl;
    cout << "Probability of AT: " << m_at_prob << endl;
    cout << "Probability of AC: " << m_ac_prob << endl;
    cout << "Probability of AG: " << m_ag_prob << endl;
    cout << "Probability of TA: " << m_ta_prob << endl;
    cout << "Probability of TT: " << m_tt_prob << endl;
    cout << "Probability of TC: " << m_tc_prob << endl;
    cout << "Probability of TG: " << m_tg_prob << endl;
    cout << "Probability of CA: " << m_ca_prob << endl;
    cout << "Probability of CT: " << m_ct_prob << endl;
    cout << "Probability of CC: " << m_cc_prob << endl;
    cout << "Probability of CG: " << m_cg_prob << endl;
    cout << "Probability of GA: " << m_ga_prob << endl;
    cout << "Probability of GT: " << m_gt_prob << endl;
    cout << "Probability of GC: " << m_gc_prob << endl;
    cout << "Probability of GG: " << m_gg_prob << endl;
  } else {
    cout << "ERROR: Cannot open file." << endl;
  }
}

//Writes out 1000 lines of sample nucleotides that fit appropriately with the statistics found earlier
void NucleoReader::printSampleFile() {
  //Creates the seed for rand()
  srand(time(NULL));
  //The upper bounds on the values for which the nucleotides are distributed
  float a_upper_bound = m_a_prob;
  float t_upper_bound = m_a_prob + m_t_prob;
  float c_upper_bound = m_a_prob + m_t_prob + m_c_prob;
  float g_upper_bound = m_a_prob + m_t_prob + m_c_prob + m_g_prob;
  //Writes out the beginning of the 1000 lines
  cout << "\n\n10 Lines of Sample Nucleotides: " << endl;
  //Writes out 1000 lines
  for (int i = 0; i < 10; ++i) {
    //a, b, c, & d found in the hint on the assignment pdf
    float a = ((float) rand() / (RAND_MAX));
    float b = ((float) rand() / (RAND_MAX));
    float c = sqrt(-2 * log(a)) * cos(2 * M_PI * b);
    int d = (m_std_dev * c) + m_mean;
    //The current line being written out to the file
    string tempLine = "";
    //Checks to make sure d is positive
    if (d > 0) {
      //Writes out letters to the length d
      for (int j = 0; j < d; ++j) {
        //randomNum generated between 0 & 1
        float randomNum = (float) rand() / RAND_MAX;
        //c_upper_bound <= randomNum < g_upper_bound => G
        if (randomNum >= c_upper_bound && randomNum < g_upper_bound)
          tempLine += "G";
        //t_upper_bound <= randomNum < c_upper_bound => C
        else if (randomNum >= t_upper_bound && randomNum < c_upper_bound)
          tempLine += "C";
        //a_upper_bound <= randomNum < t_upper_bound => T
        else if (randomNum >= a_upper_bound && randomNum < t_upper_bound)
          tempLine += "T";
        //0 <= randomNum < a_upper_bound => A
        else
          tempLine += "A";
      }
      //Writes out the completed line to the file
      cout << tempLine << endl;
    }
    //Writes out a blank if d = 0 or is negative
    else {
      cout << endl;
    }
  }
}
