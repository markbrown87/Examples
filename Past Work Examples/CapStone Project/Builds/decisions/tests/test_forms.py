from django.test import TestCase
from decisions.forms import ScoreForm
# Create your tests here.

class ScoreFormTests(TestCase):
    def create_ScoreForm(self,x,y):
        return ScoreForm(item_count = x, criteria_count = y)

    def create_FullScoreForm(self,x=42):
        data = {"0_0" : 12, "0_1" : x, "0_2" : 98, "1_0" : 4, "1_1" : 52, "1_2" : 100}
        return ScoreForm(data=data,item_count = 2, criteria_count = 3)

    def test_ScoreFormFields(self):
        length = 12
        width = 14
        testForm = self.create_ScoreForm(length,width)
        self.assertIs(len(testForm.fields),(length*width))

    def test_ScoreFormValid(self):
        testForm = self.create_FullScoreForm()

        self.assertTrue(testForm.is_valid())

    def test_ScoreFormInValidHigh(self):
        testForm = self.create_FullScoreForm(x=200)

        self.assertFalse(testForm.is_valid())

    def test_ScoreFormInValidLow(self):
        testForm = self.create_FullScoreForm(x=-32)

        self.assertFalse(testForm.is_valid())    
