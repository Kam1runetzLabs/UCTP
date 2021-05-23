//
// Created by timas on 12.05.2021.
//

#ifndef UCTP_DATA_FOR_RUN_HPP
#define UCTP_DATA_FOR_RUN_HPP
namespace alg {
struct Block {
  int group;
  int subject;
  int subjectType;
  int teacher;

  Block(int g, int s, int st, int t)
      : group(g), subject(s), subjectType(st), teacher(t) {}
};
}  // namespace alg
#endif  // UCTP_DATA_FOR_RUN_HPP
