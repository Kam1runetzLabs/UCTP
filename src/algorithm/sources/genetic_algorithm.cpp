#include <unordered_map>
#include <algorithm>

#include "genetic_algorithm.hpp"

static constexpr int populationSize = POPULATION_SIZE_CONST

// random function
int alg::getRandomNumber(int min, int max) {
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>((rand() * fraction * (max - min + 1) + min));
}

// Gen create
const int &alg::Gen::GetValue() const { return Value; }

alg::Gen::Gen(const int val) : Value(val) {}

/*alg::Gen::Gen(const Gen& g) {
    Value = g.GetValue();
}*/

void alg::Gen::SetValue(const int &val) {
  Value = val;
}

// Chromosome of time genes
void alg::ChromosomeTime::Initialize(const std::vector<Block> &blocks, const std::vector<int> &AllTimes) {
  TimeChromosome.reserve(blocks.size());
  for (size_t i = 0; i < blocks.size(); ++i) {
    Gen newGen(AllTimes[getRandomNumber(0, static_cast<int>(AllTimes.size()))]);
    TimeChromosome.push_back(newGen);
  }
}

const std::vector<alg::Gen> &alg::ChromosomeTime::GetTimeGenes() {
  return TimeChromosome;
}

void alg::ChromosomeTime::NewMutationTime(const int i, const std::vector<int> &AllTimes) {
  TimeChromosome[i].SetValue(AllTimes[getRandomNumber(0, static_cast<int>(AllTimes.size()))]);
}

void alg::ChromosomeTime::CopyParts(const std::vector<Gen> &firstPart,
                                    const std::vector<Gen> &secondPart,
                                    int part) {
  for (int i = 0; i < part; ++i) {
    Gen newGen(firstPart[i]);
    TimeChromosome.push_back(newGen);
  }
  for (size_t i = part; i < secondPart.size(); ++i) {
    Gen newGen(secondPart[i]);
    TimeChromosome.push_back(newGen);
  }
}

// Chromosome of Auditory Genes

void alg::ChromosomeAuditory::Initialize(const std::vector<Block> &blocks, const std::vector<int> &AuditoryType1,
                                         const std::vector<int> &AuditoryType2) {
  AuditoryChromosome.reserve(blocks.size());
  for (auto block: blocks) {
    if (block.subjectType == 1) {
      Gen newGen(AuditoryType1[getRandomNumber(0, static_cast<int>(AuditoryType1.size()))]);
      AuditoryChromosome.push_back(newGen);
    } else {
      Gen newGen(AuditoryType2[getRandomNumber(0, static_cast<int>(AuditoryType2.size()))]);
      AuditoryChromosome.push_back(newGen);
    }
  }
}

const std::vector<alg::Gen> &alg::ChromosomeAuditory::GetAuditoryGenes() {
  return AuditoryChromosome;
}

void alg::ChromosomeAuditory::NewMutationAuditory(const int i, const std::vector<Block> &blocks,
                                                  const std::vector<int> &AuditoryType1,
                                                  const std::vector<int> &AuditoryType2) {
  if (blocks[i].subjectType == 1) {
    AuditoryChromosome[i].SetValue(AuditoryType1[getRandomNumber(0, static_cast<int>(AuditoryType1.size()))]);
  } else if (blocks[i].subjectType == 2) {
    AuditoryChromosome[i].SetValue(AuditoryType1[getRandomNumber(0, static_cast<int>(AuditoryType2.size()))]);
  }
}

void alg::ChromosomeAuditory::CopyParts(const std::vector<Gen> &firstPart,
                                        const std::vector<Gen> &secondPart,
                                        int part) {
  for (int i = 0; i < part; ++i) {
    Gen newGen(firstPart[i]);
    AuditoryChromosome.push_back(newGen);
  }
  for (size_t i = part; i < secondPart.size(); ++i) {
    Gen newGen(secondPart[i]);
    AuditoryChromosome.push_back(newGen);
  }
}

// Individual, contains Time and Auditory chromosomes
alg::Individual::Individual() {
  ChromAud = std::make_shared<ChromosomeAuditory>();
  ChromTime = std::make_shared<ChromosomeTime>();
}

void alg::Individual::Initialize(const std::vector<Block> &blocks, const std::vector<int> &AuditoryType1,
                                 const std::vector<int> &AuditoryType2, const std::vector<int> &AllTimes) {
  CreateNewChromosomeAuditory(blocks, AuditoryType1, AuditoryType2);
  CreateNewChromosomeTime(blocks, AllTimes);
}

void alg::Individual::CreateNewChromosomeTime(const std::vector<Block> &blocks,
                                              const std::vector<int> &AllTimes) {
  ChromTime->Initialize(blocks, AllTimes);
}

void
alg::Individual::CreateNewChromosomeAuditory(const std::vector<Block> &blocks, const std::vector<int> &AuditoryType1,
                                             const std::vector<int> &AuditoryType2) {
  ChromAud->Initialize(blocks, AuditoryType1, AuditoryType2);
}

std::shared_ptr<alg::ChromosomeAuditory> alg::Individual::GetAuditoryChromosome() {
  return ChromAud;
}

std::shared_ptr<alg::ChromosomeTime> alg::Individual::GetTimeChromosome() {
  return ChromTime;
}

void alg::Individual::Crossing(const std::shared_ptr<Individual> &Ind1, const std::shared_ptr<Individual> &Ind2,
                               const std::vector<Block> &blocks) {
  int partEdge = getRandomNumber(0, blocks.size());
  ChromAud->CopyParts(Ind1->GetAuditoryChromosome()->GetAuditoryGenes(),
                      Ind2->GetAuditoryChromosome()->GetAuditoryGenes(), partEdge);
  ChromTime->CopyParts(Ind1->GetTimeChromosome()->GetTimeGenes(), Ind2->GetTimeChromosome()->GetTimeGenes(),
                       partEdge);
}

void alg::Individual::Mutate(const std::vector<Block> &blocks, const std::vector<int> &AuditoryType1,
                             const std::vector<int> &AuditoryType2, const std::vector<int> &AllTimes) {
  ChromAud->NewMutationAuditory(getRandomNumber(0, blocks.size()), blocks, AuditoryType1, AuditoryType2);
  ChromTime->NewMutationTime(getRandomNumber(0, blocks.size()), AllTimes);
}

// Population, contains all Individuals
alg::Population::Population() : sizeIndividuals(0) {}

alg::Population::Population(const std::vector<Block> &blcks, const std::vector<int> &AudType1,
                            const std::vector<int> &AudType2,
                            const std::vector<int> &AllTmes) : sizeIndividuals(0) {
  blocks = blcks;
  AuditoryType1 = AudType1;
  AuditoryType2 = AudType2;
  AllTimes = AllTmes;
}

void alg::Population::InitializeInds() {
  for (int i = 0; i < populationSize; ++i) {
    std::shared_ptr<Individual> newIndividual(new Individual);
    newIndividual->Initialize(blocks, AuditoryType1, AuditoryType2, AllTimes);
    Individuals.push_back(newIndividual);
    sizeIndividuals++;
  }
}

std::shared_ptr<alg::Individual> alg::Population::Iterations() {
  InitializeInds();
  for (int i = 0; i < 3; ++i) {
    NewPopulation();
    Crossingover();
    Mutation();
  }
  return SearchBest();
}

void alg::Population::NewPopulation() {
  AllRules allRules;
  allRules.SetRules();

  for (auto i : Individuals) {
    allRules.calcFitness(i, blocks);
  }

  std::vector<int> Pen = allRules.GetPenaltyList();
  std::sort(Pen.begin(), Pen.end());
  int populationEdge = Pen[Pen.size() / 2];

  std::vector<std::shared_ptr<Individual>> NewPopulation;
  for (size_t i = 0; i < allRules.GetPenaltyList().size(); ++i) {
    if (allRules.GetPenaltyList()[i] < populationEdge) {
      NewPopulation.push_back(Individuals[i]);
    }
  }

  sizeIndividuals = NewPopulation.size();
  Individuals.clear();
  Individuals = std::move(NewPopulation);
}

void alg::Population::Crossingover() {
  for (int i = 0; i < sizeIndividuals - 1; i = i + 2) {
    std::shared_ptr<Individual> newIndividual1 = std::make_shared<Individual>();
    newIndividual1->Crossing(Individuals[i], Individuals[i + 1], blocks);
    Individuals.push_back(newIndividual1);

    std::shared_ptr<Individual> newIndividual2 = std::make_shared<Individual>();
    newIndividual2->Crossing(Individuals[i + 1], Individuals[i], blocks);
    Individuals.push_back(newIndividual2);
  }

  sizeIndividuals = Individuals.size();
}

void alg::Population::Mutation() {
  for (auto &Ind : Individuals) {
    Ind->Mutate(blocks, AuditoryType1, AuditoryType2, AllTimes);
  }
}

std::shared_ptr<alg::Individual> alg::Population::SearchBest() {
  AllRules allRules;
  allRules.SetRules();

  for (auto i : Individuals) {
    allRules.calcFitness(i, blocks);
  }

  std::vector<int> Pen = allRules.GetPenaltyList();
  std::sort(Pen.begin(), Pen.end());
  int populationBest = Pen[0];
  for (size_t i = 0; i < allRules.GetPenaltyList().size(); ++i) {
    if (allRules.GetPenaltyList()[i] == populationBest) {
      return Individuals[i];
    }
  }

  return nullptr;
}

std::vector<std::shared_ptr<alg::Individual>> alg::Population::GetPopulation() {
  return Individuals;
}

// All Rules
void alg::AllRules::SetRules() {
  std::shared_ptr<IRule> rule1(new SameGroupMoreBlock);
  if (rule1 == nullptr) {
    return;
  }
  Rules.push_back(rule1);

  std::shared_ptr<IRule> rule2(new SameLecMoreBlock);
  if (rule2 == nullptr) {
    return;
  }
  Rules.push_back(rule2);

  std::shared_ptr<IRule> rule3(new SameAudSameTime);
  if (rule3 == nullptr) {
    return;
  }
  Rules.push_back(rule3);
}

int alg::AllRules::calcFitness(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks) {
  if (Ind == nullptr) {
    return -1;
  }

  int flawCnt = 0;
  for (auto rule : Rules) {
    flawCnt += rule->CalcRule(Ind, blocks);
  }

  SetPenalty(flawCnt);
  return flawCnt;
}

void alg::AllRules::SetPenalty(int cnt) {
  Penalty.push_back(cnt);
}

std::vector<int> &alg::AllRules::GetPenaltyList() {
  return Penalty;
}

void alg::AllRules::ForWordMutation(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks,
                                    const std::vector<int> &AllTimes) {
  if (Ind == nullptr) {
    return;
  }

  for (auto rule : Rules) {
    rule->ForWordMutation(Ind, blocks, AllTimes);
  }
}

void alg::AllRules::RandomMutation(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks,
                                   const std::vector<int> &AuditoryType1,
                                   const std::vector<int> &AuditoryType2, const std::vector<int> &AllTimes) {
  if (Ind == nullptr) {
    return;
  }

  for (auto &rule : Rules) {
    rule->RandomMutation(Ind, blocks, AuditoryType1, AuditoryType2, AllTimes);
  }
}


// Same auditory same time for one group rule
alg::SameAudSameTime::SameAudSameTime() : R(0) {}

void alg::SameAudSameTime::ForWordMutation(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks,
                                           const std::vector<int> &AllTimes) {
  if (Ind == nullptr) {
    return;
  }

  for (size_t i = 0; i < blocks.size(); ++i) {
    for (size_t j = i + 1; j < blocks.size() - 1; ++j) {
      if (Ind->GetAuditoryChromosome()->GetAuditoryGenes()[i].GetValue() ==
          Ind->GetAuditoryChromosome()->GetAuditoryGenes()[j].GetValue() &&
          Ind->GetTimeChromosome()->GetTimeGenes()[i].GetValue() ==
          Ind->GetTimeChromosome()->GetTimeGenes()[j].GetValue()) {
        Ind->GetTimeChromosome()->NewMutationTime(static_cast<int>(i), AllTimes);
      }
    }
  }
}

int alg::SameAudSameTime::CalcRule(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks) {
  if (Ind == nullptr) {
    return -1;
  }

  int flawCnt = 0;
  for (size_t i = 0; i < blocks.size(); ++i) {
    for (size_t j = i + 1; j < blocks.size() - 1; ++j) {
      if (Ind->GetAuditoryChromosome()->GetAuditoryGenes()[i].GetValue() ==
          Ind->GetAuditoryChromosome()->GetAuditoryGenes()[j].GetValue() &&
          Ind->GetTimeChromosome()->GetTimeGenes()[i].GetValue() ==
          Ind->GetTimeChromosome()->GetTimeGenes()[j].GetValue()) {
        flawCnt++;
      }
    }
  }

  return flawCnt;
}

void alg::SameAudSameTime::SetR(const std::vector<Block> &blocks) {
  R = getRandomNumber(0, blocks.size());
}

void alg::SameAudSameTime::RandomMutation(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks,
                                          const std::vector<int> &AuditoryType1,
                                          const std::vector<int> &AuditoryType2, const std::vector<int> &AllTimes) {
  if (Ind == nullptr) {
    return;
  }

  SetR(blocks);
  Ind->GetTimeChromosome()->NewMutationTime(R, AllTimes);
  Ind->GetAuditoryChromosome()->NewMutationAuditory(R, blocks, AuditoryType1, AuditoryType2);
}

int alg::SameAudSameTime::GetR() const {
  return R;
}

// Only one lesson for one group same time
alg::SameGroupMoreBlock::SameGroupMoreBlock() : R(0) {}

void alg::SameGroupMoreBlock::ForWordMutation(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks,
                                              const std::vector<int> &AllTimes) {
  if (Ind == nullptr) {
    return;
  }

  for (size_t i = 0; i < blocks.size(); ++i) {
    for (size_t j = i + 1; j < blocks.size() - 1; ++j) {
      if (blocks[i].group == blocks[j].group &&
          Ind->GetTimeChromosome()->GetTimeGenes()[i].GetValue() ==
          Ind->GetTimeChromosome()->GetTimeGenes()[j].GetValue()) {
        Ind->GetTimeChromosome()->NewMutationTime(static_cast<int>(i), AllTimes);
      }
    }
  }
}

int alg::SameGroupMoreBlock::CalcRule(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks) {
  if (Ind == nullptr) {
    return -1;
  }

  int flawCnt = 0;
  for (size_t i = 0; i < blocks.size(); ++i) {
    for (size_t j = i + 1; j < blocks.size() - 1; ++j) {
      if (blocks[i].group == blocks[j].group &&
          Ind->GetTimeChromosome()->GetTimeGenes()[i].GetValue() ==
          Ind->GetTimeChromosome()->GetTimeGenes()[j].GetValue()) {
        flawCnt++;
      }
    }
  }
  return flawCnt;
}

void alg::SameGroupMoreBlock::SetR(const std::vector<Block> &blocks) {
  R = getRandomNumber(0, blocks.size());
}

void alg::SameGroupMoreBlock::RandomMutation(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks,
                                             const std::vector<int> &AuditoryType1,
                                             const std::vector<int> &AuditoryType2, const std::vector<int> &AllTimes) {
  if (Ind == nullptr) {
    return;
  }

  SetR(blocks);
  Ind->GetTimeChromosome()->NewMutationTime(R, AllTimes);
  Ind->GetAuditoryChromosome()->NewMutationAuditory(R, blocks, AuditoryType1, AuditoryType2);
}

int alg::SameGroupMoreBlock::GetR() const {
  return R;
}

// Teacher has only one lesson one time
alg::SameLecMoreBlock::SameLecMoreBlock() : R(0) {}

void alg::SameLecMoreBlock::ForWordMutation(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks,
                                            const std::vector<int> &AllTimes) {
  if (Ind == nullptr) {
    return;
  }

  for (size_t i = 0; i < blocks.size(); ++i) {
    for (size_t j = i + 1; j < blocks.size() - 1; ++j) {
      if (blocks[i].teacher == blocks[j].teacher &&
          Ind->GetTimeChromosome()->GetTimeGenes()[i].GetValue() ==
          Ind->GetTimeChromosome()->GetTimeGenes()[j].GetValue()) {
        Ind->GetTimeChromosome()->NewMutationTime(static_cast<int>(i), AllTimes);
      }
    }
  }
}

int alg::SameLecMoreBlock::CalcRule(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks) {
  if (Ind == nullptr) {
    return -1;
  }

  int flawCnt = 0;
  for (size_t i = 0; i < blocks.size(); ++i) {
    for (size_t j = i + 1; j < blocks.size() - 1; ++j) {
      if (blocks[i].teacher == blocks[j].teacher &&
          Ind->GetTimeChromosome()->GetTimeGenes()[i].GetValue() ==
          Ind->GetTimeChromosome()->GetTimeGenes()[j].GetValue()) {
        flawCnt++;
      }
    }
  }
  return flawCnt;
}

void alg::SameLecMoreBlock::SetR(const std::vector<Block> &blocks) {
  R = getRandomNumber(0, blocks.size());
}

void alg::SameLecMoreBlock::RandomMutation(std::shared_ptr<Individual> &Ind, const std::vector<Block> &blocks,
                                           const std::vector<int> &AuditoryType1,
                                           const std::vector<int> &AuditoryType2, const std::vector<int> &AllTimes) {
  if (Ind == nullptr) {
    return;
  }

  SetR(blocks);
  Ind->GetTimeChromosome()->NewMutationTime(R, AllTimes);
  Ind->GetAuditoryChromosome()->NewMutationAuditory(R, blocks, AuditoryType1, AuditoryType2);
}

int alg::SameLecMoreBlock::GetR() const {
  return R;
}
