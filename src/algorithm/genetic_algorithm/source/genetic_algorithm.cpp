#include <genetic_algorithm.hpp>
#include <unordered_map>

int getRandomNumber(int min, int max) {
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int Gen::GetValue() const { return Value; }
Gen::Gen(int val) {}

void ChromosomeTime::Initialize(const std::vector<Block>& blocks) {}
std::vector<std::shared_ptr<Gen>> ChromosomeTime::GetTimeGenes() {
  return TimeChromosome;
}
void ChromosomeTime::NewMutationTime(int i, const std::vector<Block>& blocks) {}
ChromosomeTime::ChromosomeTime() {}

void ChromosomeAuditory::Initialize(const std::vector<Block>& blocks) {}
std::vector<std::shared_ptr<Gen>> ChromosomeAuditory::GetAuditoryGenes() {
  return AuditoryChromosome;
}
void ChromosomeAuditory::NewMutationAuditory(int i, const std::vector<Block>& blocks) {}
ChromosomeAuditory::ChromosomeAuditory() {}

Individual::Individual() : Value(0) {
  ChromAud = std::make_shared<ChromosomeAuditory>();
  ChromTime = std::make_shared<ChromosomeTime>();
}
void Individual::Initialize() {
  CreateNewChromosomeAuditory();
  CreateNewChromosomeTime();
}
void Individual::CreateNewChromosomeTime() {}
void Individual::CreateNewChromosomeAuditory() {}
std::shared_ptr<ChromosomeAuditory> Individual::GetAuditoryChromosome() {
  return ChromAud;
}
std::shared_ptr<ChromosomeTime> Individual::GetTimeChromosome() {
  return ChromTime;
}
double Individual::FitnessFunction() {
  ChromAud->GetAuditoryGenes();
  return 0;
}
void Individual::ComputeFitness() {}

Population::Population() : sizeIndividuals(0) {}
void Population::InitializeInds() {
  std::shared_ptr<Individual> newIndividual(new Individual);
  newIndividual->Initialize();
  newIndividual->FitnessFunction();
  Individuals.push_back(newIndividual);

  NewPopulation(Individuals);
}
double Population::Iterations() {
  InitializeInds();
  NewPopulation(Individuals);
  Crossingover(Individuals);
  Mutation(Individuals);
  SearchBest();

  return sizeIndividuals;
}
void Population::NewPopulation(
    std::vector<std::shared_ptr<Individual>> OldPopulation) {}
void Population::Crossingover(std::vector<std::shared_ptr<Individual>> IndSv) {}
void Population::Mutation(std::vector<std::shared_ptr<Individual>> IndS) {}
std::shared_ptr<Individual> Population::SearchBest() {
  return std::shared_ptr<Individual>();
}
std::vector<std::shared_ptr<Individual>> Population::GetPopulation() {
  return Individuals;
}

void AllRules::SetRules() {}
int AllRules::calcFitness(std::shared_ptr<Individual>& Ind) { return 0; }
void AllRules::ForWordMutation(std::shared_ptr<Individual>& Ind) {}
void AllRules::SetPenalty(int cnt) {}

SameAudSameTime::SameAudSameTime() {}
void SameAudSameTime::ForWordMutation(std::shared_ptr<Individual>& Ind) {}
int SameAudSameTime::CalcRule(std::shared_ptr<Individual>& Ind) { return 0; }
int SameAudSameTime::GetR() { return 0; }

void SameGroupMoreBlock::ForWordMutation(std::shared_ptr<Individual>& Ind) {}
int SameGroupMoreBlock::CalcRule(std::shared_ptr<Individual>& Ind) { return 0; }
int SameGroupMoreBlock::GetR() { return 0; }
SameGroupMoreBlock::SameGroupMoreBlock() {}

void SameLecMoreBlock::ForWordMutation(std::shared_ptr<Individual>& Ind) {}
int SameLecMoreBlock::CalcRule(std::shared_ptr<Individual>& Ind) { return 0; }
int SameLecMoreBlock::GetR() { return 0; }
SameLecMoreBlock::SameLecMoreBlock() {}
