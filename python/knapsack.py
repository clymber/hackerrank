#!/usr/bin/env python
# _*_ coding: utf-8 _*_
from functools import cached_property
from sys import stdin

class ShoppingItem:
    def __init__(self, seq:int=0, price:int=0, weigh:int=0, master:int=0):
        self.seq = seq # Sequential number.
        self.price = price # Price of the item.
        self.weigh = weigh # How important it is.
        self.master = master

    @cached_property
    def happiness(self) -> int:
        return self.price * self.weigh

class ShoppingKit:
    def __init__(self, masterpiece:ShoppingItem):
        self.items = [masterpiece]
    
    def add_accessories(self, accessories:list[ShoppingItem]):
        self.items.extend(accessories)

    @cached_property
    def cost_perf(self) -> list[tuple[int:int]]:
        cp = [(self.items[0].price, self.items[0].happiness)]
        for a in self.items[1:]:
            cp.extend([(c + a.price, p + a.happiness) for c, p in cp])
        return cp

def load_shoppinglist(count:int, istream=stdin) -> list[ShoppingKit]:
    masterpieces, accessories = [], []

    for seq in range(1, count+1):
        price, weigh, master = map(int, istream.readline().strip().split())
        item = ShoppingItem(seq, price, weigh, master)
        if master == 0:
            masterpieces.append(ShoppingKit(item))
        else:
            accessories.append(item)

    for m in masterpieces:
        items = filter(lambda x: x.master==m.items[0].seq, accessories)
        m.add_accessories(items)

    return masterpieces

def knapsack_shopping(balance:int, shoplist:list[ShoppingKit]) -> int:
    if len(shoplist) == 0:
        return 0

    happiness = [0 for _ in range(balance+1)]

    for kit in shoplist:
        cost_perf = kit.cost_perf
        for budget in range(balance, 0, -1):
            for cost, value in filter(lambda x: x[0]<= budget, cost_perf):
                if happiness[budget] >= happiness[budget - cost] + value:
                    continue
                happiness[budget] = happiness[budget - cost] + value

    return happiness[-1]

