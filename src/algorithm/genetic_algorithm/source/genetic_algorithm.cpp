#include <genetic_algorithm.hpp>
#include <unordered_map>
#include <algorithm>

static constexpr int populationSize = POPULATION_SIZE_CONST

// random function
int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// Gen create
int Gen::GetValue() const { return Value; }

Gen::Gen(int val) : Value(val) {}

Gen::Gen(std::shared_ptr<Gen> g) {
    Value = g->GetValue();
}

// Chromosome of time genes
ChromosomeTime::ChromosomeTime() {
    for (int i = 0; i < 100; ++i) {
        AllTimes.push_back(i);
    }
}

void ChromosomeTime::Initialize(const std::vector<Block>& blocks) {
    for (auto block : blocks) {
        std::shared_ptr<Gen> newGen(new Gen(AllTimes[getRandomNumber(0, AllTimes.size())]));
        TimeChromosome.push_back(newGen);
    }
}

std::vector<std::shared_ptr<Gen>> ChromosomeTime::GetTimeGenes() {
    return TimeChromosome;
}

void ChromosomeTime::NewMutationTime(const int i,
                                     const std::vector<Block>& blocks) {
    std::shared_ptr<Gen> newGen(new Gen(AllTimes[getRandomNumber(0, AllTimes.size())]));
    TimeChromosome[i] = newGen;
}

void ChromosomeTime::CopyParts(std::vector<std::shared_ptr<Gen>> firstPart, std::vector<std::shared_ptr<Gen>> secondPart, int part) {
    for (int i = 0; i < part; ++i) {
        std::shared_ptr<Gen> newGen(new Gen(firstPart[i]));
        TimeChromosome.push_back(newGen);
    }
    for (int i = part; i < secondPart.size(); ++i) {
        std::shared_ptr<Gen> newGen(new Gen(secondPart[i]));
        TimeChromosome.push_back(newGen);
    }
}

// Chromosome of Auditory Genes
ChromosomeAuditory::ChromosomeAuditory() {
    for (int i = 0; i < 50; ++i) {
        AuditoryType1.push_back(i);
    }
    for (int i = 50; i < 100; ++i) {
        AuditoryType2.push_back(i);
    }
}

void ChromosomeAuditory::Initialize(const std::vector<Block>& blocks) {
    for (auto block : blocks) {
        if (block.subjectType == 1) {
            std::shared_ptr<Gen> newGen(new Gen(AuditoryType1[getRandomNumber(0, AuditoryType1.size())]));
            AuditoryChromosome.push_back(newGen);
        } else {
            std::shared_ptr<Gen> newGen(new Gen(AuditoryType2[getRandomNumber(0, AuditoryType1.size())]));
            AuditoryChromosome.push_back(newGen);
        }
    }
}

std::vector<std::shared_ptr<Gen>> ChromosomeAuditory::GetAuditoryGenes() {
    return AuditoryChromosome;
}

void ChromosomeAuditory::NewMutationAuditory(const int i, const std::vector<Block>& blocks) {
    if (blocks[i].subjectType == 1) {
        std::shared_ptr<Gen> newGen(new Gen(AuditoryType1[getRandomNumber(0, AuditoryType1.size())]));
        AuditoryChromosome[i] = newGen;
    } else if (blocks[i].subjectType == 2) {
        std::shared_ptr<Gen> newGen(new Gen(AuditoryType1[getRandomNumber(0, AuditoryType2.size())]));
        AuditoryChromosome[i] = newGen;
    }
}

void ChromosomeAuditory::CopyParts(std::vector<std::shared_ptr<Gen>> firstPart, std::vector<std::shared_ptr<Gen>> secondPart, int part) {
    for (int i = 0; i < part; ++i) {
        std::shared_ptr<Gen> newGen(new Gen(firstPart[i]));
        AuditoryChromosome.push_back(newGen);
    }
    for (int i = part; i < secondPart.size(); ++i) {
        std::shared_ptr<Gen> newGen(new Gen(secondPart[i]));
        AuditoryChromosome.push_back(newGen);
    }
}

// Individual, contains Time and Auditory chromosomes
Individual::Individual() {
    ChromAud = std::make_shared<ChromosomeAuditory>();
    ChromTime = std::make_shared<ChromosomeTime>();

    for (int i = 0; i < 255; ++i) {
        Block newBlock = Block(i, i, getRandomNumber(1, 2));
        blocks.push_back(newBlock);
    }
}

void Individual::Initialize() {
    CreateNewChromosomeAuditory();
    CreateNewChromosomeTime();
}

void Individual::CreateNewChromosomeTime() { ChromTime->Initialize(blocks); }

void Individual::CreateNewChromosomeAuditory() { ChromAud->Initialize(blocks); }

std::shared_ptr<ChromosomeAuditory> Individual::GetAuditoryChromosome() {
    return ChromAud;
}

std::shared_ptr<ChromosomeTime> Individual::GetTimeChromosome() {
    return ChromTime;
}

void Individual::Crossing(std::shared_ptr<Individual> Ind1, std::shared_ptr<Individual> Ind2) {
    int partEdge = getRandomNumber(0, blocks.size());
    ChromAud->CopyParts(Ind1->GetAuditoryChromosome()->GetAuditoryGenes(), Ind2->GetAuditoryChromosome()->GetAuditoryGenes(), partEdge);
    ChromTime->CopyParts(Ind1->GetTimeChromosome()->GetTimeGenes(), Ind2->GetTimeChromosome()->GetTimeGenes(), partEdge);
}

void Individual::Mutate() {
    ChromAud->NewMutationAuditory(getRandomNumber(0, blocks.size()), blocks);
    ChromTime->NewMutationTime(getRandomNumber(0, blocks.size()), blocks);
}

// Population, contains all Individuals
Population::Population() : sizeIndividuals(0) {}

void Population::InitializeInds() {
    for (int i = 0; i < populationSize; ++i) {
        std::shared_ptr<Individual> newIndividual(new Individual);
        newIndividual->Initialize();
        Individuals.push_back(newIndividual);
        sizeIndividuals++;
    }
}

double Population::Iterations() {
    InitializeInds();
    for (int i = 0; i < 10; ++i) {
        NewPopulation();
        Crossingover();
        Mutation();
    }
    SearchBest();

    return sizeIndividuals;
}

void Population::NewPopulation() {
    AllRules allRules;
    allRules.SetRules();

    for (auto i : Individuals) {
        allRules.calcFitness(i);
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
    Individuals = NewPopulation;
}

void Population::Crossingover() {
    for (int i = 0; i < sizeIndividuals - 1; i = i + 2) {
        std::shared_ptr<Individual> newIndividual1 = std::make_shared<Individual>();
        newIndividual1->Crossing(Individuals[i], Individuals[i + 1]);
        Individuals.push_back(newIndividual1);

        std::shared_ptr<Individual> newIndividual2 = std::make_shared<Individual>();
        newIndividual2->Crossing(Individuals[i + 1], Individuals[i]);
        Individuals.push_back(newIndividual2);
    }

    sizeIndividuals = Individuals.size();
}

void Population::Mutation() {
    for (auto Ind : Individuals) {
        Ind->Mutate();
    }
}

std::shared_ptr<Individual> Population::SearchBest() {
    AllRules allRules;
    allRules.SetRules();

    for (auto i : Individuals) {
        allRules.calcFitness(i);
    }

    std::vector<int> Pen = allRules.GetPenaltyList();
    std::sort(Pen.begin(), Pen.end());
    int populationBest = Pen[0];
    for (size_t i = 0; i < allRules.GetPenaltyList().size(); ++i) {
        if (allRules.GetPenaltyList()[i] == populationBest) {
            return Individuals[i];
        }
    }
}

std::vector<std::shared_ptr<Individual>> Population::GetPopulation() {
    return Individuals;
}

// All Rules
void AllRules::SetRules() {
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

int AllRules::calcFitness(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return -1;
    }

    int flawCnt = 0;
    for (auto rule : Rules) {
        flawCnt += rule->CalcRule(Ind);
    }

    SetPenalty(flawCnt);
    return flawCnt;
}

void AllRules::SetPenalty(int cnt) {
    Penalty.push_back(cnt);
}

std::vector<int>& AllRules::GetPenaltyList() {
    return Penalty;
}

void AllRules::ForWordMutation(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return;
    }

    for (auto rule : Rules) {
        rule->ForWordMutation(Ind);
    }
}

void AllRules::RandomMutation(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return;
    }

    for (auto rule : Rules) {
        rule->RandomMutation(Ind);
    }
}


// Same auditory same time for one group rule
SameAudSameTime::SameAudSameTime() : R(0) {
    for (int i = 0; i < 255; ++i) {
        Block newBlock = Block(i, i, getRandomNumber(1, 2));
        Blocks.push_back(newBlock);
    }
    for (int i = 0; i < 50; ++i) {
        AuditoryType1.push_back(i);
    }
    for (int i = 50; i < 100; ++i) {
        AuditoryType2.push_back(i);
    }
    for (int i = 0; i < 100; ++i) {
        AllTimes.push_back(i);
    }
}

void SameAudSameTime::ForWordMutation(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return;
    }

    for (int i = 0; i < Ind->GetAuditoryChromosome()->GetAuditoryGenes().size(); ++i) {
        for (int j = i + 1; j < Ind->GetAuditoryChromosome()->GetAuditoryGenes().size() - 1; ++j) {
            if (Ind->GetAuditoryChromosome()->GetAuditoryGenes()[i]->GetValue() ==
                Ind->GetAuditoryChromosome()->GetAuditoryGenes()[j]->GetValue() &&
                Ind->GetTimeChromosome()->GetTimeGenes()[i]->GetValue() ==
                Ind->GetTimeChromosome()->GetTimeGenes()[j]->GetValue()) {
                Ind->GetTimeChromosome()->NewMutationTime(i, Blocks);
            }
        }
    }
}

int SameAudSameTime::CalcRule(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return -1;
    }

    int flawCnt = 0;
    for (size_t i = 0; i < Ind->GetAuditoryChromosome()->GetAuditoryGenes().size(); ++i) {
        for (size_t j = i + 1; j < Ind->GetAuditoryChromosome()->GetAuditoryGenes().size() - 1; ++j) {
            if (Ind->GetAuditoryChromosome()->GetAuditoryGenes()[i]->GetValue() ==
                Ind->GetAuditoryChromosome()->GetAuditoryGenes()[j]->GetValue() &&
                Ind->GetTimeChromosome()->GetTimeGenes()[i]->GetValue() ==
                Ind->GetTimeChromosome()->GetTimeGenes()[j]->GetValue()) {
                flawCnt++;
            }
        }
    }

    return flawCnt;
}

void SameAudSameTime::SetR() {
    R = getRandomNumber(0, Blocks.size());
}

void SameAudSameTime::RandomMutation(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return;
    }

    SetR();
    Ind->GetTimeChromosome()->NewMutationTime(R, Blocks);
    Ind->GetAuditoryChromosome()->NewMutationAuditory(R, Blocks);
}

int SameAudSameTime::GetR() const {
    return R;
}

// Only one lesson for one group same time
SameGroupMoreBlock::SameGroupMoreBlock() : R(0) {
    for (int i = 0; i < 255; ++i) {
        Block newBlock = Block(i, i, getRandomNumber(1, 2));
        Blocks.push_back(newBlock);
    }
    for (int i = 0; i < 100; ++i) {
        AllTimes.push_back(i);
    }
}

void SameGroupMoreBlock::ForWordMutation(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return;
    }

    for (int i = 0; i < Blocks.size(); ++i) {
        for (int j = i + 1; j < Blocks.size() - 1; ++j) {
            if (Blocks[i].group == Blocks[j].group &&
                Ind->GetTimeChromosome()->GetTimeGenes()[i]->GetValue() ==
                Ind->GetTimeChromosome()->GetTimeGenes()[j]->GetValue()) {
                Ind->GetTimeChromosome()->NewMutationTime(i, Blocks);
            }
        }
    }
}

int SameGroupMoreBlock::CalcRule(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return -1;
    }

    int flawCnt = 0;
    for (int i = 0; i < Blocks.size(); ++i) {
        for (int j = i + 1; j < Blocks.size() - 1; ++j) {
            if (Blocks[i].group == Blocks[j].group &&
                Ind->GetTimeChromosome()->GetTimeGenes()[i]->GetValue() ==
                Ind->GetTimeChromosome()->GetTimeGenes()[j]->GetValue()) {
                flawCnt++;
            }
        }
    }
    return flawCnt;
}

void SameGroupMoreBlock::SetR() {
    R = getRandomNumber(0, Blocks.size());
}

void SameGroupMoreBlock::RandomMutation(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return;
    }

    SetR();
    Ind->GetTimeChromosome()->NewMutationTime(R, Blocks);
}

int SameGroupMoreBlock::GetR() const {
    return R;
}

// Teacher has only one lesson one time
SameLecMoreBlock::SameLecMoreBlock() : R(0) {
    for (int i = 0; i < 255; ++i) {
        Block newBlock = Block(i, i, getRandomNumber(1, 2));
        Blocks.push_back(newBlock);
    }
    for (int i = 0; i < 100; ++i) {
        AllTimes.push_back(i);
    }
}

void SameLecMoreBlock::ForWordMutation(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return;
    }

    for (int i = 0; i < Blocks.size(); ++i) {
        for (int j = i + 1; j < Blocks.size() - 1; ++j) {
            if (Blocks[i].teacher == Blocks[j].teacher &&
                Ind->GetTimeChromosome()->GetTimeGenes()[i]->GetValue() ==
                Ind->GetTimeChromosome()->GetTimeGenes()[j]->GetValue()) {
                Ind->GetTimeChromosome()->NewMutationTime(i, Blocks);
            }
        }
    }
}

int SameLecMoreBlock::CalcRule(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return -1;
    }

    int flawCnt = 0;
    for (int i = 0; i < Blocks.size(); ++i) {
        for (int j = i + 1; j < Blocks.size() - 1; ++j) {
            if (Blocks[i].teacher == Blocks[j].teacher &&
                Ind->GetTimeChromosome()->GetTimeGenes()[i]->GetValue() ==
                Ind->GetTimeChromosome()->GetTimeGenes()[j]->GetValue()) {
                flawCnt++;
            }
        }
    }
    return flawCnt;
}

void SameLecMoreBlock::SetR() {
    R = getRandomNumber(0, Blocks.size());
}

void SameLecMoreBlock::RandomMutation(std::shared_ptr<Individual>& Ind) {
    if (Ind == nullptr) {
        return;
    }

    SetR();
    Ind->GetTimeChromosome()->NewMutationTime(R, Blocks);
}

int SameLecMoreBlock::GetR() const {
    return R;
}
