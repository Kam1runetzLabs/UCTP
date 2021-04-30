#ifndef UCTP_GENETIC_ALGORITHM_HPP
#define UCTP_GENETIC_ALGORITHM_HPP

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#define POPULATION_SIZE_CONST 255;

int getRandomNumber(int min, int max);

struct Block {
  int group;
  int subject;
  int subjectType;
  int teacher;

  Block(int g, int s, int st) : group(g), subject(s), subjectType(st) {}
};

class Gen {
  int Value;

 public:
  explicit Gen(int val);

  int GetValue() const;
};

class ChromosomeTime {
  std::vector<int> AllTimes;

  std::vector<std::shared_ptr<Gen>> TimeChromosome;

 public:
  explicit ChromosomeTime();

  void Initialize(const std::vector<Block>& blocks);

  std::vector<std::shared_ptr<Gen>> GetTimeGenes();

  void NewMutationTime(int i, const std::vector<Block>& blocks);
};

class ChromosomeAuditory {
  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;

  std::vector<std::shared_ptr<Gen>> AuditoryChromosome;

 public:
  explicit ChromosomeAuditory();

  void Initialize(const std::vector<Block>& blocks);

  std::vector<std::shared_ptr<Gen>> GetAuditoryGenes();

  void NewMutationAuditory(int i, const std::vector<Block>& blocks);
};

class Individual {
  double Value;
  std::shared_ptr<ChromosomeAuditory> ChromAud;
  std::shared_ptr<ChromosomeTime> ChromTime;
  std::vector<Block> blocks;

 public:
  explicit Individual();

  void Initialize();

  void CreateNewChromosomeTime();

  void CreateNewChromosomeAuditory();

  std::shared_ptr<ChromosomeAuditory> GetAuditoryChromosome();

  std::shared_ptr<ChromosomeTime> GetTimeChromosome();

  double FitnessFunction();

  void ComputeFitness();
};

class Population {
  std::vector<std::shared_ptr<Individual>> Individuals;
  int sizeIndividuals;

 public:
  explicit Population();

  void InitializeInds();

  double Iterations();

  void NewPopulation(std::vector<std::shared_ptr<Individual>> OldPopulation);

  void Crossingover(std::vector<std::shared_ptr<Individual>> IndSv);

  void Mutation(std::vector<std::shared_ptr<Individual>> IndS);

  std::shared_ptr<Individual> SearchBest();

  std::vector<std::shared_ptr<Individual>> GetPopulation();
};

class IRule {
 public:
  virtual ~IRule() = default;

  virtual void ForWordMutation(std::shared_ptr<Individual>& Ind) = 0;

  virtual int CalcRule(std::shared_ptr<Individual>& Ind) = 0;
};

class SameAudSameTime : public IRule {
  int R;
  std::vector<Block> Blocks;
  std::vector<int> AllTimes;
  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;

 public:
  explicit SameAudSameTime();

  void ForWordMutation(std::shared_ptr<Individual>& Ind) override;

  int CalcRule(std::shared_ptr<Individual>& Ind) override;

  int GetR();
};

class SameGroupMoreBlock : public IRule {
  int R;
  std::vector<Block> Blocks;
  std::vector<int> AllTimes;

 public:
  explicit SameGroupMoreBlock();

  void ForWordMutation(std::shared_ptr<Individual>& Ind) override;

  int CalcRule(std::shared_ptr<Individual>& Ind) override;

  int GetR();
};

class SameLecMoreBlock : public IRule {
  int R;
  std::vector<Block> Blocks;
  std::vector<int> AllTimes;

 public:
  explicit SameLecMoreBlock();

  void ForWordMutation(std::shared_ptr<Individual>& Ind) override;

  int CalcRule(std::shared_ptr<Individual>& Ind) override;

  int GetR();
};

class AllRules {
  std::vector<IRule*> Rules;
  std::vector<int> Penalty;

 public:
  void SetRules();

  int calcFitness(std::shared_ptr<Individual>& Ind);

  void SetPenalty(int cnt);

  void ForWordMutation(std::shared_ptr<Individual>& Ind);
};

#endif  // UCTP_GENETIC_ALGORITHM_HPP
