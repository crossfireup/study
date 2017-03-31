#!/bin/env python
#-*- coding:utf-8 -*-

from collections import OrderedDict

if __name__ == '__main__':
     s = "nH89akfCqT0G/DRxKv4loohZavgaraVShRP82u+gCymB13zAmrlPTGot1IHhidzEuDAkx+Fzxr1mjomJTLYmSBTHJaos3cwmfwKQuPEf75Gehsn04AaKBtRKH62/Wml1WvFF/Jk6CqYjX/XP/xZAeqLmkBl6oKv+51D4+oyBSKkpK84JtRKM8VygWXb+hK9a/AT+oF/7"
     char_count = OrderedDict()
     cur_char = None

     for i in s:
         if i in char_count.keys():
             char_count[i] += 1
         else:
             char_count[i] = 1

     print char_count


