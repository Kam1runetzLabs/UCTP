#ifndef UCTP_GENETIC_ALGORITHM_HPP
#define UCTP_GENETIC_ALGORITHM_HPP

#include <iostream>
#include <memory>
#include <vector>

struct Block {};

class Gen {
  int Value;

 public:
  int GetValue() const;
};

class ChromosomeTime {
  std::vector<int> AllTimes;

  std::vector<std::shared_ptr<Gen>> TimeChromosome;

 public:
  explicit ChromosomeTime();
  void Initialize(Block* blockd);
  std::vector<std::shared_ptr<Gen>> GetTimeGenes();
  void NewMutationTime();
};

class ChromosomeAuditory {
  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;

  std::vector<std::shared_ptr<Gen>> AuditoryChromosome;

 public:
  explicit ChromosomeAuditory();
  void Initialize(Block* blockd);
  std::vector<std::shared_ptr<Gen>> GetAuditoryGenes();
  void NewMutationAuditory();
};

class Individual {
  double Value;
  std::shared_ptr<ChromosomeAuditory> ChromAud;
  std::shared_ptr<ChromosomeTime> ChromTime;

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
  virtual void ForWordMutation(Individual Ind) = 0;
  virtual int CalcRule(Individual Ind) = 0;
  virtual std::vector<int> AllTimes() = 0;
};

class SameAudSameTime : IRule {
  int R;

 public:
  void ForWordMutation(Individual Ind) override;
  int CalcRule(Individual Ind) override;
  std::vector<int> AllTimes() override;
  std::vector<int> Blocks();
  std::vector<int> AuditoryType1();
  std::vector<int> AuditoryType2();
  int GetR();
};

class SameGroupMoreBlock : IRule {
  int R;

 public:
  void ForWordMutation(Individual Ind) override;
  int CalcRule(Individual Ind) override;
  std::vector<int> AllTimes() override;
  std::unordered_map<int, int[]> DirGroup();
  int GetR();
};

class SameLecMoreBlock : IRule {
  int R;

 public:
  void ForWordMutation(Individual Ind) override;
  int CalcRule(Individual Ind) override;
  std::vector<int> AllTimes() override;
  std::unordered_map<int, int[]> DirLec();
  int GetR();
};

class AllRules {
  std::vector<IRule> Rules;
  std::vector<int> Penalty;

 public:
  void GetRules();
  double calcFitness(Individual Inds);
  int GetPenalty(int cnt);
};

#endif  // UCTP_GENETIC_ALGORITHM_HPP
