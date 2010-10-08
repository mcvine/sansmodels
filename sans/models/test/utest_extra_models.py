"""
    Unit tests for extra models,PolymerexclVolume, RPA10Model
"""
import unittest
class TestPolymerExclVolume(unittest.TestCase):
    """
        Unit tests for PolymerexclVolume (non-shape) function
    """
    def setUp(self):
        from sans.models.PolymerExclVolume import PolymerExclVolume
        self.model= PolymerExclVolume()
        
    def test1D(self):          
        # the values are from Igor pro calculation    
        self.assertAlmostEqual(self.model.run(0.001), 0.998801, 6)
        self.assertAlmostEqual(self.model.run(0.21571), 0.00192041, 6)
        self.assertAlmostEqual(self.model.runXY(0.41959), 0.000261302, 6)
        
class TestPolymerExclVolume(unittest.TestCase):
    """
        Unit tests for RPA10Model (non-shape) function
    """
    def setUp(self):
        from sans.models.RPA10Model import RPA10Model
        self.model0= RPA10Model(0)
        self.model1= RPA10Model(1)
        self.model2= RPA10Model(2)
        self.model3= RPA10Model(3)
        self.model4= RPA10Model(4)
        self.model5= RPA10Model(5)
        self.model6= RPA10Model(6)
        self.model7= RPA10Model(7)
        self.model8= RPA10Model(8)
        self.model9= RPA10Model(9)
        
    def test1D(self):          
        # the test values are from Igor pro calculation   
        # case 0 
        # set default of vol fration consistent with IGor
        self.model0.setParam('Phic',0.5)
        self.model0.setParam('Phid',0.5)
        self.assertAlmostEqual(self.model0.run(0.001), 0.0716863, 6)
        self.assertAlmostEqual(self.model0.runXY(0.414955), 0.00396997, 6)
        # case 1
        # set default of vol fration consistent with IGor
        self.model1.setParam('Phic',0.5)
        self.model1.setParam('Phid',0.5)
        self.assertAlmostEqual(self.model1.run(0.001), 0.00395016, 6)
        self.assertAlmostEqual(self.model1.runXY(0.414955), 0.00396735, 6)
        # case 2 
        # set default of vol fration consistent with IGor
        self.model2.setParam('Phib',0.33)
        self.model2.setParam('Phic',0.33)
        self.model2.setParam('Phid',0.33)
        self.assertAlmostEqual(self.model2.run(0.001), 0.0932902, 6)
        self.assertAlmostEqual(self.model2.runXY(0.414955), 0.00355736, 6)
        # case 3
        # set default of vol fration consistent with IGor
        self.model3.setParam('Phib',0.33)
        self.model3.setParam('Phic',0.33)
        self.model3.setParam('Phid',0.33)
        self.assertAlmostEqual(self.model3.run(0.001), 0.026254, 6)
        self.assertAlmostEqual(self.model3.runXY(0.414955), 0.00355577, 6)
        # case 4
        # set default of vol fration consistent with IGor
        self.model4.setParam('Phib',0.33)
        self.model4.setParam('Phic',0.33)
        self.model4.setParam('Phid',0.33)
        self.assertAlmostEqual(self.model4.run(0.001), 0.0067433, 6)
        self.assertAlmostEqual(self.model4.runXY(0.414955), 0.00355656, 6)
        # case 5
        self.assertAlmostEqual(self.model5.run(0.001), 0.102636, 6)
        self.assertAlmostEqual(self.model5.runXY(0.414955), 0.00305812, 6)
        # case 6
        self.assertAlmostEqual(self.model6.run(0.001), 0.0370357, 6)
        self.assertAlmostEqual(self.model6.runXY(0.414955), 0.00305708, 6)
        # case 7
        self.assertAlmostEqual(self.model7.run(0.001), 0.0167775, 6)
        self.assertAlmostEqual(self.model7.runXY(0.414955), 0.00305743, 6)
        # case 8
        self.assertAlmostEqual(self.model8.run(0.001), 0.0378691, 6)
        self.assertAlmostEqual(self.model8.runXY(0.414955), 0.00305743, 6)
        # case 9
        self.assertAlmostEqual(self.model9.run(0.001), 0.00839376, 6)
        self.assertAlmostEqual(self.model9.runXY(0.414955), 0.00305777, 6)        
        
if __name__ == '__main__':
    unittest.main()