// WordCount.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

void error(string info)
{
  cout << "[ERROR] " << info;
}

bool output(string name, int phrase_len, bool read_folder, int topk, string filename)
{
  std::fstream ss(filename, std::fstream::out);
  // if (!ss) { return false; }
  /* output basic info */
  TextReader* reader;
  if (phrase_len == 1)
  {
    reader = new WordReader();
  }
  else
  {
    reader = new PhraseReader(phrase_len);
  }
  if (read_folder)
  {
    reader->ReadFolder(name);
  }
  else
  {
    if (!reader->ReadFile(name)) { error("No such file."); }
  }
  ss << "characters: " << reader->char_count()+1 << endl;
  ss << "words: " << reader->word_count() << endl;
  ss << "lines: " << reader->line_count() << endl;
  /* output topk info */
  LimitedHeap<TextRecorder, std::greater<TextRecorder>> heap(topk);
  for (TextReader::CountTree::iterator it = reader->begin(); it != reader->end(); it++)
  {
    string text = it->first;
    int count = it->second;
    heap.Push(TextRecorder(text, count));
  }
  heap.Sort();
  for (std::vector<TextRecorder>::iterator it = heap.begin(); it != heap.end(); it++)
  {
    ss << it->text() << ": " << it->count() << endl;
  }
  /* output to file */
  ss.close();
  return true;
}

int main(int argc, char* argv[])
{
  const string      kOutFilename = "result.txt";
  enum              {SET, UNSET, SETTING};
  string            name;
  bool              read_folder = false;
  int               phrase_len = 1;
  int               topk = 10;
  int               name_status = UNSET;
  int               phrase_len_status = UNSET;
  int               topk_status = UNSET;
  for (int i = 1; i < argc; i++)
  {
    char* para = argv[i];
    if (SETTING == phrase_len_status)
    {
      phrase_len = atoi(para);
      phrase_len_status = SET;
    }
    else if (SETTING == topk_status)
    {
      topk = atoi(para);
      topk_status = SET;
    }
    else if (0 == strcmp(para, "-r") && !read_folder)
    { 
      read_folder = true;
    }
    else if (0 == strcmp(para, "-m") && UNSET == phrase_len_status)
    {
      phrase_len_status = SETTING;
    }
    else if (0 == strcmp(para, "-n") && UNSET == topk_status)
    {
      topk_status = SETTING;
    }
    else if (UNSET == name_status)
    {
      name = para;
      name_status = SET;
    }
    else
    {
      error("Invalid Para.");
    }
  }
  if (UNSET == name_status)
  {
    error("Lack path.");
  }
  output(name, phrase_len, read_folder, topk, kOutFilename);
  return 0;
}
