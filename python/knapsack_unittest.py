#!/usr/bin/env python
# _*_ coding: utf-8 _*_

import unittest
from io import StringIO
from knapsack import *

class TestShoppingKit(unittest.TestCase):
    def setUp(self):
        self.master = ShoppingItem(1, 5, 6, 0)
        self.accessories = [
            ShoppingItem(2, 20, 4, 1),
            ShoppingItem(3, 30, 2, 1),
            ShoppingItem(4, 10, 2, 1)
        ]

    def test_init(self):
        kit = ShoppingKit(self.master)
        self.assertEqual(kit.items[0], self.master)
    
    def test_add_accessories(self):
        kit = ShoppingKit(self.master)
        kit.add_accessories(self.accessories)
        self.assertEqual(len(kit.items), 4)

class TestKnapsackShopList(unittest.TestCase):
    def setUp(self):
        self.testinput = StringIO("50 5\n"
            "20 3 5\n"
            "20 3 5\n"
            "10 3 0\n"
            "10 2 0\n"
            "10 1 0")
        self.expect = 130
    
    def test_get_shopping_kits(self):
        _, count = map(int, self.testinput.readline().strip().split())
        self.assertEqual(count, 5)
        sk = load_shoppinglist(count, self.testinput)
        
        self.assertEqual(len(sk), 3)
        self.assertEqual(len(sk[0].items), 1)
        self.assertEqual(len(sk[1].items), 1)
        self.assertEqual(len(sk[2].items), 3)
        self.assertEqual(sk[2].items[0].seq, 5)
        self.assertEqual(sk[2].items[1].master, 5)
        self.assertEqual(sk[2].items[2].price, 20)
    
    def test_knapsack_shoplist(self):
        balance, count = map(int, self.testinput.readline().strip().split())
        self.assertEqual(count, 5)
        sk = load_shoppinglist(count, self.testinput)
        self.assertEqual(knapsack_shopping(balance, sk), self.expect)

    def test_knapsack_shoplist2(self):
        input2 = StringIO("1000 5\n"
            "800 2 0\n"
            "400 5 1\n"
            "300 5 1\n"
            "400 3 0\n"
            "500 2 0")
        expect2 = 2200
        balance, count = map(int, input2.readline().strip().split())
        self.assertEqual(count, 5)
        sk = load_shoppinglist(count, input2)
        self.assertEqual(knapsack_shopping(balance, sk), expect2)

    def test_knapsack_shoplist3(self):
        input2 = StringIO("2000 10\n"
            "500 1 0\n"
            "400 4 0\n"
            "300 5 1\n"
            "400 5 1\n"
            "200 5 0\n"
            "500 4 5\n"
            "400 4 0\n"
            "320 2 0\n"
            "410 3 0\n"
            "400 3 5")
        expect2 = 7430
        balance, count = map(int, input2.readline().strip().split())
        self.assertEqual(count, 10)
        sk = load_shoppinglist(count, input2)
        self.assertEqual(len(sk), 6)
        self.assertEqual(knapsack_shopping(balance, sk), expect2)

if __name__ == '__main__':
    unittest.main()

