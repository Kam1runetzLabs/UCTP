#ifndef UCTP_GENETIC_ALGORITHM_HPP
#define UCTP_GENETIC_ALGORITHM_HPP

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#define POPULATION_SIZE_CONST 60;

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
    Gen(std::shared_ptr<Gen> g);

    int GetValue() const;
};

class ChromosomeTime {
    std::vector<int> AllTimes;

    std::vector<std::shared_ptr<Gen>> TimeChromosome;

public:
    explicit ChromosomeTime();

    void CopyParts(std::vector<std::shared_ptr<Gen>> firstPart, std::vector<std::shared_ptr<Gen>> secondPart, int part);

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

    void CopyParts(std::vector<std::shared_ptr<Gen>> firstPart, std::vector<std::shared_ptr<Gen>> secondPart, int part);

    void Initialize(const std::vector<Block>& blocks);

    std::vector<std::shared_ptr<Gen>> GetAuditoryGenes();

    void NewMutationAuditory(int i, const std::vector<Block>& blocks);
};

class Individual {
    std::shared_ptr<ChromosomeAuditory> ChromAud;
    std::shared_ptr<ChromosomeTime> ChromTime;
    std::vector<Block> blocks;

public:
    explicit Individual();

    void Crossing(std::shared_ptr<Individual> Ind1, std::shared_ptr<Individual> Ind2);

    void Mutate();

    void Initialize();

    void CreateNewChromosomeTime();

    void CreateNewChromosomeAuditory();

    std::shared_ptr<ChromosomeAuditory> GetAuditoryChromosome();

    std::shared_ptr<ChromosomeTime> GetTimeChromosome();
};

class Population {
    std::vector<std::shared_ptr<Individual>> Individuals;
    int sizeIndividuals;

public:
    explicit Population();

    void InitializeInds();

    double Iterations();

    void NewPopulation();

    void Crossingover();

    void Mutation();

    std::shared_ptr<Individual> SearchBest();

    std::vector<std::shared_ptr<Individual>> GetPopulation();
};

class IRule {
public:
    virtual ~IRule() = default;

    virtual void ForWordMutation(std::shared_ptr<Individual>& Ind) = 0;

    virtual int CalcRule(std::shared_ptr<Individual>& Ind) = 0;

    virtual void RandomMutation(std::shared_ptr<Individual>& Ind) = 0;
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

    void RandomMutation(std::shared_ptr<Individual>& Ind) override;

    void SetR();

    int GetR() const;
};

class SameGroupMoreBlock : public IRule {
    int R;
    std::vector<Block> Blocks;
    std::vector<int> AllTimes;

public:
    explicit SameGroupMoreBlock();

    void ForWordMutation(std::shared_ptr<Individual>& Ind) override;

    int CalcRule(std::shared_ptr<Individual>& Ind) override;

    void RandomMutation(std::shared_ptr<Individual>& Ind) override;

    void SetR();

    int GetR() const;
};

class SameLecMoreBlock : public IRule {
    int R;
    std::vector<Block> Blocks;
    std::vector<int> AllTimes;

public:
    explicit SameLecMoreBlock();

    void ForWordMutation(std::shared_ptr<Individual>& Ind) override;

    int CalcRule(std::shared_ptr<Individual>& Ind) override;

    void RandomMutation(std::shared_ptr<Individual>& Ind) override;

    void SetR();

    int GetR() const;
};

class AllRules {
    std::vector<std::shared_ptr<IRule>> Rules;
    std::vector<int> Penalty;

public:
    void SetRules();

    int calcFitness(std::shared_ptr<Individual>& Ind);

    void SetPenalty(int cnt);

    std::vector<int>& GetPenaltyList();

    void ForWordMutation(std::shared_ptr<Individual>& Ind);

    void RandomMutation(std::shared_ptr<Individual>& Ind);
};

#endif  // UCTP_GENETIC_ALGORITHM_HPP
