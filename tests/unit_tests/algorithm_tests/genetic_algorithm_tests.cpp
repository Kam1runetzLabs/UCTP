#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <genetic_algorithm.hpp>

TEST(GeneticALgorithmTests, PopulationWorkTest) {
  std::vector<Block> blocks;
  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;
  std::vector<int> AllTimes;

  blocks.reserve(255);
  for (int i = 0; i < 255; ++i) {
    Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
    blocks.push_back(newBlock);
  }
  AuditoryType1.reserve(50);
  for (int i = 0; i < 50; ++i) {
    AuditoryType1.push_back(i);
  }
  AuditoryType2.reserve(50);
  for (int i = 50; i < 100; ++i) {
    AuditoryType2.push_back(i);
  }
  AllTimes.reserve(50);
  for (int i = 0; i < 100; ++i) {
    AllTimes.push_back(i);
  }

  alg::Population myPopulation(blocks, AuditoryType1, AuditoryType2, AllTimes);
  std::shared_ptr<alg::Individual> bestInd = myPopulation.Iterations();

  alg::AllRules allRules;
  allRules.SetRules();
  EXPECT_EQ(allRules.calcFitness(bestInd, blocks), 0);
}

TEST(GeneticALgorithmTests, NewPopulationWorkTest) {
  std::vector<Block> blocks;
  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;
  std::vector<int> AllTimes;

  for (int i = 0; i < 255; ++i) {
    Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
    blocks.push_back(newBlock);
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
  alg::Population myPopulation(blocks, AuditoryType1, AuditoryType2, AllTimes);

  myPopulation.InitializeInds();
  EXPECT_EQ(myPopulation.GetPopulation().size(), 60);
}

TEST(GeneticAlgorithmTests, IndividualSucsessWorkTest) {
  alg::Individual myIndividual;

  std::vector<Block> blocks;
  for (int i = 0; i < 255; ++i) {
    Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
    blocks.push_back(newBlock);
  }

  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;
  for (int i = 0; i < 50; ++i) {
    AuditoryType1.push_back(i);
  }
  for (int i = 50; i < 100; ++i) {
    AuditoryType2.push_back(i);
  }

  std::vector<int> AllTimes;
  for (int i = 0; i < 100; ++i) {
    AllTimes.push_back(i);
  }

  myIndividual.Initialize(blocks, AuditoryType1, AuditoryType2, AllTimes);
  EXPECT_TRUE(myIndividual.GetAuditoryChromosome() != nullptr);
  EXPECT_TRUE(myIndividual.GetTimeChromosome() != nullptr);
}

class GeneticAlgorithmChromosomeTests : public ::testing::Test {
 protected:
  std::vector<Block> blocks;

  virtual void SetUp() {
    for (int i = 0; i < 255; ++i) {
      Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
      blocks.push_back(newBlock);
    }
  }

  virtual void TearDown() {}
};

TEST_F(GeneticAlgorithmChromosomeTests, ChromosomeTimeGeneralTest) {
  alg::ChromosomeTime myChromosomeTime;

  std::vector<int> AllTimes;
  for (int i = 0; i < 100; ++i) {
    AllTimes.push_back(i);
  }

  myChromosomeTime.Initialize(blocks, AllTimes);
  EXPECT_EQ(myChromosomeTime.GetTimeGenes().size(), blocks.size());
}

TEST_F(GeneticAlgorithmChromosomeTests, ChromosomeTimeChangeGenTest) {
  alg::ChromosomeTime myChromosomeTime;

  std::vector<int> AllTimes;
  for (int i = 0; i < 100; ++i) {
    AllTimes.push_back(i);
  }

  myChromosomeTime.Initialize(blocks, AllTimes);

  int replaceableGen = 3;
  int OldGen = myChromosomeTime.GetTimeGenes()[replaceableGen].GetValue();
  myChromosomeTime.NewMutationTime(replaceableGen, AllTimes);
  int NewGen = myChromosomeTime.GetTimeGenes()[replaceableGen].GetValue();

  EXPECT_TRUE(OldGen != NewGen);
}

TEST_F(GeneticAlgorithmChromosomeTests, ChromosomeAuditoryGeneralTest) {
  alg::ChromosomeTime myChromosomeTime;

  std::vector<int> AllTimes;
  for (int i = 0; i < 100; ++i) {
    AllTimes.push_back(i);
  }

  myChromosomeTime.Initialize(blocks, AllTimes);
  EXPECT_EQ(myChromosomeTime.GetTimeGenes().size(), blocks.size());
}

TEST_F(GeneticAlgorithmChromosomeTests, ChromosomeAuditoryChangeGenTest) {
  alg::ChromosomeAuditory myChromosomeAuditory;

  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;
  AuditoryType1.reserve(50);
  for (int i = 0; i < 50; ++i) {
    AuditoryType1.push_back(i);
  }
  AuditoryType2.reserve(50);
  for (int i = 50; i < 100; ++i) {
    AuditoryType2.push_back(i);
  }

  myChromosomeAuditory.Initialize(blocks, AuditoryType1, AuditoryType2);

  int replaceableGen = 3;
  int OldGen = myChromosomeAuditory.GetAuditoryGenes()[replaceableGen].GetValue();
  myChromosomeAuditory.NewMutationAuditory(replaceableGen, blocks, AuditoryType1, AuditoryType2);
  int NewGen = myChromosomeAuditory.GetAuditoryGenes()[replaceableGen].GetValue();

  EXPECT_TRUE(OldGen != NewGen);
}

class GeneticAlgorithmRuleTests : public ::testing::Test {
 protected:
  std::shared_ptr<alg::Individual> myIndividual;
  std::vector<Block> blocks;
  std::vector<int> AuditoryType1;
  std::vector<int> AuditoryType2;
  std::vector<int> AllTimes;

  virtual void SetUp() {
    for (int i = 0; i < 255; ++i) {
      Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
      blocks.push_back(newBlock);
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

    myIndividual = std::make_shared<alg::Individual>();
    myIndividual->Initialize(blocks, AuditoryType1, AuditoryType2, AllTimes);
  }

  virtual void TearDown() {}
};

TEST(GeneticAlgorithmTests, RuleTestSameAudSameTimeInvalidIndivid) {
  std::shared_ptr<alg::Individual> myIndividual;

  std::vector<Block> blocks;
  for (int i = 0; i < 255; ++i) {
    Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
    blocks.push_back(newBlock);
  }

  alg::SameAudSameTime myRule;
  EXPECT_EQ(myRule.CalcRule(myIndividual, blocks), -1);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameAudSameTime) {
  alg::SameAudSameTime myRule;
  int prevFlaws = myRule.CalcRule(myIndividual, blocks);
  myRule.ForWordMutation(myIndividual, blocks, AllTimes);
  int newFlaws = myRule.CalcRule(myIndividual, blocks);
  EXPECT_TRUE(prevFlaws >= newFlaws);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameAudSameTimeRandomMutation) {
  alg::SameAudSameTime myRule;
  myRule.RandomMutation(myIndividual, blocks, AuditoryType1, AuditoryType2, AllTimes);

  EXPECT_TRUE(myRule.GetR() != 0);
}

TEST(GeneticAlgorithmTests, RuleTestSameGroupMoreBlockInvalidIndivid) {
  std::shared_ptr<alg::Individual> myIndividual;

  std::vector<Block> blocks;
  for (int i = 0; i < 255; ++i) {
    Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
    blocks.push_back(newBlock);
  }

  alg::SameGroupMoreBlock myRule;
  EXPECT_EQ(myRule.CalcRule(myIndividual, blocks), -1);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameGroupMoreBlockRandomMutation) {
  alg::SameGroupMoreBlock myRule;
  myRule.RandomMutation(myIndividual, blocks, AuditoryType1, AuditoryType2, AllTimes);

  EXPECT_TRUE(myRule.GetR() >= 0);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameGroupMoreBlock) {
  alg::SameGroupMoreBlock myRule;
  int prevFlaws = myRule.CalcRule(myIndividual, blocks);
  myRule.ForWordMutation(myIndividual, blocks, AllTimes);
  int newFlaws = myRule.CalcRule(myIndividual, blocks);
  EXPECT_TRUE(prevFlaws >= newFlaws);
}

TEST(GeneticAlgorithmTests, RuleTestSameLecMoreBlockInvalidIndivid) {
  std::shared_ptr<alg::Individual> myIndividual;

  std::vector<Block> blocks;
  for (int i = 0; i < 255; ++i) {
    Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
    blocks.push_back(newBlock);
  }

  alg::SameLecMoreBlock myRule;
  EXPECT_EQ(myRule.CalcRule(myIndividual, blocks), -1);
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameLecMoreBlock) {
  alg::SameLecMoreBlock myRule;
  int prevFlaws = myRule.CalcRule(myIndividual, blocks);
  myRule.ForWordMutation(myIndividual, blocks, AllTimes);
  int newFlaws = myRule.CalcRule(myIndividual, blocks);
  if (prevFlaws != 0) {
    EXPECT_TRUE(prevFlaws != newFlaws);
  }
}

TEST_F(GeneticAlgorithmRuleTests, RuleTestSameLecMoreBlockRandomMutation) {
  alg::SameLecMoreBlock myRule;
  myRule.RandomMutation(myIndividual, blocks, AuditoryType1, AuditoryType2, AllTimes);

  EXPECT_TRUE(myRule.GetR() >= 0);
}

TEST_F(GeneticAlgorithmRuleTests, AllRuleTestCalcFlaws) {
  int flawAll1 = 0;
  alg::SameGroupMoreBlock rule1;
  flawAll1 += rule1.CalcRule(myIndividual, blocks);
  alg::SameLecMoreBlock rule2;
  flawAll1 += rule2.CalcRule(myIndividual, blocks);
  alg::SameAudSameTime rule3;
  flawAll1 += rule3.CalcRule(myIndividual, blocks);

  int flawAll2 = 0;
  alg::AllRules allRules;
  allRules.SetRules();
  flawAll2 += allRules.calcFitness(myIndividual, blocks);
  EXPECT_EQ(flawAll1, flawAll2);
}

TEST_F(GeneticAlgorithmRuleTests, AllRuleTestMutation) {
  alg::AllRules allRules;
  int prevFlaws = allRules.calcFitness(myIndividual, blocks);
  allRules.ForWordMutation(myIndividual, blocks, AllTimes);
  int newFlaws = allRules.calcFitness(myIndividual, blocks);
  EXPECT_TRUE(prevFlaws >= newFlaws);
}

TEST(GeneticAlgorithmTests, AllRulesInvalidIndivid) {
  std::shared_ptr<alg::Individual> myIndividual;

  std::vector<Block> blocks;
  for (int i = 0; i < 255; ++i) {
    Block newBlock = Block(i, i, alg::getRandomNumber(1, 2), i);
    blocks.push_back(newBlock);
  }

  alg::AllRules allRules;
  allRules.SetRules();
  EXPECT_EQ(allRules.calcFitness(myIndividual, blocks), -1);
}
