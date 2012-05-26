#include "mementooriginators.h"

#include "gtest/gtest.h"

using namespace undoredo::memento;
using namespace undoredo::memento::test;

class MyOriginatorMementoTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
	  teststring="test";
	  teststring2=" test ";
  }

  MyOriginator O;
  std::string teststring;
  std::string teststring2;
};

TEST_F(MyOriginatorMementoTests, SaveState) {
 MyOriginator::MementoType Memento=O.SaveState();
	
 ASSERT_NE(nullptr,Memento);
}

TEST_F(MyOriginatorMementoTests, GetSavedState) {
	MyOriginator::MementoType Memento=O.SaveState();

	ASSERT_EQ("",Memento->GetSavedState().Get());

	O.Set(teststring);

	Memento=O.SaveState();

	ASSERT_EQ(teststring,Memento->GetSavedState().Get());
}

TEST_F(MyOriginatorMementoTests, RestoreState) {
	O.Set(teststring);

	MyOriginator::MementoType Memento=O.SaveState();

	O.Set(teststring2);
	MyOriginator::MementoType Memento2=O.SaveState();

	ASSERT_EQ(teststring2,Memento2->GetSavedState().Get());

	O.RestoreState(Memento2);

	ASSERT_EQ(teststring2,O.Get());
}
