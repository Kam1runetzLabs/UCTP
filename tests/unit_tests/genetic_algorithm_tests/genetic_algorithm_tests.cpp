#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <genetic_algorithm.hpp>


TEST(GeneticALgorithmTests, PopulationWorkTest) {
  Population myPopulation;
  ASSERT_EQ(myPopulation.Iterations(), 1);
}

TEST(GeneticALgorithmTests, NewPopulationWorkTest) {
  Population myPopulation;

  myPopulation.InitializeInds();
  EXPECT_EQ(myPopulation.GetPopulation().size(), 255);
}

TEST(GeneticAlgorithmTests, IndividualSucsessWorkTest) {
  Individual myIndividual;

  myIndividual.Initialize();
  EXPECT_TRUE(myIndividual.GetAuditoryChromosome() != nullptr);
  EXPECT_TRUE(myIndividual.GetTimeChromosome() != nullptr);
}

TEST(GeneticAlgorithmTests, ChromosomeTimeTest) {
  ChromosomeTime myChromosomeTime;
  auto *blocks = new Block;

  myChromosomeTime.Initialize(blocks);
  EXPECT_EQ(myChromosomeTime.GetTimeGenes().size(), 255);
}

TEST(GeneticAlgorithmTests, ChromosomeAuditoryTest) {
  ChromosomeTime myChromosomeAuditory;
  auto *blocks = new Block;

  myChromosomeAuditory.Initialize(blocks);
  EXPECT_EQ(myChromosomeAuditory.GetTimeGenes().size(), 255);
}

TEST(GeneticAlgorithmTests, RuleTestSameAudSameTime) {
  Individual myIndividual;
  myIndividual.Initialize();

  SameAudSameTime myRule;
  myRule.CalcRule(myIndividual);
  myRule.ForWordMutation(myIndividual);
  EXPECT_EQ(myRule.GetR(), 0);
}

TEST(GeneticAlgorithmTests, RuleTestSameGroupMoreBlock) {
  Individual myIndividual;
  myIndividual.Initialize();

  SameGroupMoreBlock myRule;
  myRule.CalcRule(myIndividual);
  myRule.ForWordMutation(myIndividual);
  EXPECT_EQ(myRule.GetR(), 0);
}

TEST(GeneticAlgorithmTests, RuleTestSameLecMoreBlock) {
  Individual myIndividual;
  myIndividual.Initialize();

  SameLecMoreBlock myRule;
  myRule.CalcRule(myIndividual);
  myRule.ForWordMutation(myIndividual);
  EXPECT_EQ(myRule.GetR(), 0);
}

