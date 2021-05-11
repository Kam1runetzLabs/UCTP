#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <genetic_algorithm.hpp>

TEST(GeneticALgorithmTests, PopulationWorkTest) {
    Population myPopulation;
    ASSERT_EQ(myPopulation.Iterations(), 60);
}

TEST(GeneticALgorithmTests, NewPopulationWorkTest) {
    Population myPopulation;

    myPopulation.InitializeInds();
    EXPECT_EQ(myPopulation.GetPopulation().size(), 60);
}

TEST(GeneticAlgorithmTests, IndividualSucsessWorkTest) {
    Individual myIndividual;

    myIndividual.Initialize();
    EXPECT_TRUE(myIndividual.GetAuditoryChromosome() != nullptr);
    EXPECT_TRUE(myIndividual.GetTimeChromosome() != nullptr);
}

class GeneticAlgorithmChromosomeTests : public ::testing::Test {
protected:
    std::vector<Block> blocks;

    virtual void SetUp() {
        for (int i = 0; i < 255; ++i) {
            Block newBlock = Block(i, i, getRandomNumber(1, 2));
            blocks.push_back(newBlock);
        }
    }

    virtual void TearDown() {
    }
};

TEST_F(GeneticAlgorithmChromosomeTests, ChromosomeTimeGeneralTest) {
    ChromosomeTime myChromosomeTime;

    myChromosomeTime.Initialize(blocks);
    EXPECT_EQ(myChromosomeTime.GetTimeGenes().size(), blocks.size());
}

TEST_F(GeneticAlgorithmChromosomeTests, ChromosomeTimeChangeGenTest) {
    ChromosomeTime myChromosomeTime;

    myChromosomeTime.Initialize(blocks);

    int replaceableGen = 3;
    int OldGen = myChromosomeTime.GetTimeGenes()[replaceableGen]->GetValue();
    myChromosomeTime.NewMutationTime(replaceableGen, blocks);
    int NewGen = myChromosomeTime.GetTimeGenes()[replaceableGen]->GetValue();

    EXPECT_TRUE(OldGen != NewGen);
}

TEST_F(GeneticAlgorithmChromosomeTests, ChromosomeAuditoryGeneralTest) {
    ChromosomeTime myChromosomeAuditory;

    myChromosomeAuditory.Initialize(blocks);
    EXPECT_EQ(myChromosomeAuditory.GetTimeGenes().size(), blocks.size());
}

TEST_F(GeneticAlgorithmChromosomeTests, ChromosomeAuditoryChangeGenTest) {
    ChromosomeAuditory myChromosomeAuditory;

    myChromosomeAuditory.Initialize(blocks);

    int replaceableGen = 3;
    int OldGen = myChromosomeAuditory.GetAuditoryGenes()[replaceableGen]->GetValue();
    myChromosomeAuditory.NewMutationAuditory(replaceableGen, blocks);
    int NewGen = myChromosomeAuditory.GetAuditoryGenes()[replaceableGen]->GetValue();

    EXPECT_TRUE(OldGen != NewGen);
}

class GeneticAlgorithmRuleTests : public ::testing::Test {
protected:
    std::shared_ptr<Individual> myIndividual;

    virtual void SetUp() {
        myIndividual = std::make_shared<Individual>();
        myIndividual->Initialize();
    }

    virtual void TearDown() {
    }
};

TEST(GeneticAlgorithmTests, RuleTestSameAudSameTimeInvalidIndivid) {
    std::shared_ptr<Individual> myIndividual;

    SameAudSameTime myRule;
    EXPECT_EQ(myRule.CalcRule(myIndividual), -1);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameAudSameTime) {
    SameAudSameTime myRule;
    int prevFlaws = myRule.CalcRule(myIndividual);
    myRule.ForWordMutation(myIndividual);
    int newFlaws = myRule.CalcRule(myIndividual);
    EXPECT_TRUE(prevFlaws >= newFlaws);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameAudSameTimeRandomMutation) {
    SameAudSameTime myRule;
    myRule.RandomMutation(myIndividual);

    EXPECT_TRUE(myRule.GetR() != 0);
}

TEST(GeneticAlgorithmTests, RuleTestSameGroupMoreBlockInvalidIndivid) {
    std::shared_ptr<Individual> myIndividual;

    SameGroupMoreBlock myRule;
    EXPECT_EQ(myRule.CalcRule(myIndividual), -1);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameGroupMoreBlockRandomMutation) {
    SameGroupMoreBlock myRule;
    myRule.RandomMutation(myIndividual);

    EXPECT_TRUE(myRule.GetR() >= 0);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameGroupMoreBlock) {
    SameGroupMoreBlock myRule;
    int prevFlaws = myRule.CalcRule(myIndividual);
    myRule.ForWordMutation(myIndividual);
    int newFlaws = myRule.CalcRule(myIndividual);
    EXPECT_TRUE(prevFlaws >= newFlaws);
}


TEST(GeneticAlgorithmTests, RuleTestSameLecMoreBlockInvalidIndivid) {
    std::shared_ptr<Individual> myIndividual;

    SameLecMoreBlock myRule;
    EXPECT_EQ(myRule.CalcRule(myIndividual), -1);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameLecMoreBlock) {
    SameLecMoreBlock myRule;
    int prevFlaws = myRule.CalcRule(myIndividual);
    myRule.ForWordMutation(myIndividual);
    int newFlaws = myRule.CalcRule(myIndividual);
    EXPECT_TRUE(prevFlaws != newFlaws);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameLecMoreBlockRandomMutation) {
    SameLecMoreBlock myRule;
    myRule.RandomMutation(myIndividual);

    EXPECT_TRUE(myRule.GetR() >= 0);
}

TEST_F(GeneticAlgorithmRuleTests, AllRuleTestCalcFlaws) {
    int flawAll1 = 0;
    SameGroupMoreBlock rule1;
    flawAll1 += rule1.CalcRule(myIndividual);
    SameLecMoreBlock rule2;
    flawAll1 += rule2.CalcRule(myIndividual);
    SameAudSameTime rule3;
    flawAll1 += rule3.CalcRule(myIndividual);

    int flawAll2 = 0;
    AllRules allRules;
    allRules.SetRules();
    flawAll2 += allRules.calcFitness(myIndividual);
    EXPECT_EQ(flawAll1, flawAll2);
}

TEST_F(GeneticAlgorithmRuleTests, AllRuleTestMutation) {
    AllRules allRules;
    int prevFlaws = allRules.calcFitness(myIndividual);
    allRules.ForWordMutation(myIndividual);
    int newFlaws = allRules.calcFitness(myIndividual);
    EXPECT_TRUE(prevFlaws >= newFlaws);
}

TEST(GeneticAlgorithmTests, AllRulesInvalidIndivid) {
    std::shared_ptr<Individual> myIndividual;

    AllRules allRules;
    allRules.SetRules();
    EXPECT_EQ(allRules.calcFitness(myIndividual), -1);
}
