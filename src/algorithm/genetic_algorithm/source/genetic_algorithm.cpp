#include <genetic_algorithm.hpp>
#include <unordered_map>

int Gen::GetValue() const { return Value; }

void ChromosomeTime::Initialize(Block *blockd) {
  std::shared_ptr<Gen> newGen(new Gen);
  TimeChromosome.push_back(newGen);
}
std::vector<std::shared_ptr<Gen>> ChromosomeTime::GetTimeGenes() {
  return TimeChromosome;
}
void ChromosomeTime::NewMutationTime() {}
ChromosomeTime::ChromosomeTime() {}

void ChromosomeAuditory::Initialize(Block *blockd) {
  std::shared_ptr<Gen> newGen(new Gen);
  AuditoryChromosome.push_back(newGen);
}
std::vector<std::shared_ptr<Gen>> ChromosomeAuditory::GetAuditoryGenes() {
  return AuditoryChromosome;
}
void ChromosomeAuditory::NewMutationAuditory() {}
ChromosomeAuditory::ChromosomeAuditory() {}

Individual::Individual() : Value(0) {
  ChromAud = std::make_shared<ChromosomeAuditory>();
  ChromTime = std::make_shared<ChromosomeTime>();
}
void Individual::Initialize() {
  CreateNewChromosomeAuditory();
  CreateNewChromosomeTime();
}
void Individual::CreateNewChromosomeTime() {
  auto *blocks = new Block;
  ChromTime->Initialize(blocks);
}
void Individual::CreateNewChromosomeAuditory() {
  auto *blocks = new Block;
  ChromAud->Initialize(blocks);
}
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

void AllRules::GetRules() {}
double AllRules::calcFitness(Individual Inds) { return 0; }
int AllRules::GetPenalty(int cnt) { return 0; }

void SameAudSameTime::ForWordMutation(Individual Ind) {}
int SameAudSameTime::CalcRule(Individual Ind) { return 0; }
std::vector<int> SameAudSameTime::AllTimes() { return std::vector<int>(); }
std::vector<int> SameAudSameTime::Blocks() { return std::vector<int>(); }
std::vector<int> SameAudSameTime::AuditoryType1() { return std::vector<int>(); }
std::vector<int> SameAudSameTime::AuditoryType2() { return std::vector<int>(); }
int SameAudSameTime::GetR() { return 0; }

void SameGroupMoreBlock::ForWordMutation(Individual Ind) {}
int SameGroupMoreBlock::CalcRule(Individual Ind) { return 0; }
std::vector<int> SameGroupMoreBlock::AllTimes() { return std::vector<int>(); }
std::unordered_map<int, int[]> SameGroupMoreBlock::DirGroup() {
  return std::unordered_map<int, int[]>();
}
int SameGroupMoreBlock::GetR() { return 0; }

void SameLecMoreBlock::ForWordMutation(Individual Ind) {}
int SameLecMoreBlock::CalcRule(Individual Ind) { return 0; }
std::vector<int> SameLecMoreBlock::AllTimes() { return std::vector<int>(); }
std::unordered_map<int, int[]> SameLecMoreBlock::DirLec() {
  return std::unordered_map<int, int[]>();
}
int SameLecMoreBlock::GetR() { return 0; }
