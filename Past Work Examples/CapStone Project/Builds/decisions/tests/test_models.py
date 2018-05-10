from django.test import TestCase
from decisions.models import Decide, Criteria, Item

class DecideModelTests(TestCase):
    def test_decideStrMethod(self):
        myDecide1 = Decide(decisionName="Robert")
        myDecide2 = Decide(decisionName=" p jfd Phil")
        myDecide3 = Decide(decisionName="8927909")
        myDecide4 = Decide(decisionName="_Robert_")

        self.assertIs(str(myDecide1), "Robert")
        self.assertIs(str(myDecide2), " p jfd Phil")
        self.assertIs(str(myDecide3), "8927909")
        self.assertIs(str(myDecide4), "_Robert_")

class CriteriaModelTests(TestCase):
    def test_criteriaStrMethod(self):
        myDecide1 = Decide(decisionName="Cars")
        myDecide1.save()

        myCriteria1 = Criteria(criteriaName="Speed",criteriaWeight=50,decision=myDecide1)

        self.assertEqual(str(myCriteria1),"Speed")

        myDecide1.delete()

    #A criteria can only be saved if its decision is saved.
    #Trying to save a criteria without a decision should raise a ValueError exception.
    def test_criteriaDeleteDecision(self):
        myDecide1 = Decide(decisionName="Shoes")
        myDecide1.save()

        myCriteria1 = Criteria(criteriaName="Fit",criteriaWeight=72,decision=myDecide1)

        myDecide1.delete()

        self.assertRaises(ValueError,myCriteria1.save)

class ItemModelTests(TestCase):
    def set_up(self):
        self.decide1 = Decide(decisionName="Cars")
        self.decide1.save()
        self.item1 = Item(itemName="Honda",itemScore="0",decision=self.decide1)

    def test_criteriaStrMethod(self):
        self.set_up()
        self.assertEqual(str(self.item1),"Honda")
        self.decide1.delete()

    #An item can only be saved if its decision is saved.
    #Trying to save an item without a decision should raise a ValueError exception.
    def test_criteriaDeleteDecision(self):
        self.set_up()
        self.decide1.delete()
        self.assertRaises(ValueError,self.item1.save)
