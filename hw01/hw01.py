import sys
import math
input = int(sys.argv[1])

class P:
    def __init__(self,state,wants,cs):
        self.state = state
        self.wants = wants
        self.cs = cs
        self.prev = -1

class Q:
    def __init__(self,state,wants,cs):
        self.state = state
        self.wants = wants
        self.cs = cs
        self.prev = -1

def print_state(p,q,turn):
    print("P.state =",p.state,"P.wants =",p.wants,"P in CS =",p.cs,\
        "\nQ.state =",q.state,"Q.wants =",q.wants,"Q in CS =",q.cs,\
        "\nturn =",turn,"\n")

def both_in_cs(p,q):
    if p.cs and q.cs:
        print("No Mutual Exclusion! :-(")

def in_deadlock(p,q):
    if p.prev == p.state and q.prev == q.state:
        print("Deadlock! :-(")


def next_state_p(p,q,turn):
    p.prev = p.state
    if p.state == 1:
        p.state = 2

    elif p.state == 2:
        p.wants = True
        p.state = 3

    elif p.state == 3:
        if q.wants:
            p.state = 4
        else:
            p.state = 8
            p.cs = True

    elif p.state == 4:
        if q.wants:
            if turn == 2:
                p.state = 5
        else:
            p.state = 8
            p.cs = True

    elif p.state == 5:
        if q.wants:
            if turn == 2:
                p.wants = False
                p.state = 6
        else:
            p.state = 8
            p.cs = True

    elif p.state == 6:
        if q.wants:
            if turn == 1:
                p.state = 7
        else:
            p.state = 8             
            p.cs = True

    elif p.state == 7:
        if q.wants:
            p.wants = True
        else:
            p.state = 8
            p.cs = True

    elif p.state == 8:
        p.state = 9
        p.cs = False

    elif p.state == 9:
        turn = 2
        p.state = 10

    elif p.state == 10:
        p.wants = False
        p.state = 1

    else:
        p.state = -1
       
    print_state(p,q,turn)
    both_in_cs(p,q)
    in_deadlock(p,q) 
    return p,q,turn

def next_state_q(p,q,turn):
    q.prev = q.state
    if q.state == 1:
        q.state = 2

    elif q.state == 2:
        q.wants = True
        q.state = 3

    elif q.state == 3:
        if p.wants:
            q.state = 4
        else:
            q.state = 8
            q.cs = True

    elif q.state == 4:
        if p.wants:
            if turn == 1:
                q.state = 5
        else:
            q.state = 8
            q.cs = True

    elif q.state == 5:
        if p.wants:
            q.wants = False
            q.state = 6
        else:
            q.state = 8
            q.cs = True

    elif q.state == 6:
        if p.wants:
            if turn == 1:
                q.state = 7
        else:
            q.state = 8
            q.cs = True

    elif q.state == 7:
        if p.wants:
            q.wants = True
        else:
            q.state = 8
            q.cs = True

    elif q.state == 8:
        q.state = 9
        q.cs = False

    elif q.state == 9:
        turn = 1
        q.state = 10

    elif q.state == 10:
        q.wants = False
        q.state = 1

    else:
        q.state = -1

    print_state(p,q,turn)
    both_in_cs(p,q)
    in_deadlock(p,q)
    return p,q,turn




p = P(1,False,False)
q = Q(1,False,False)
turn = 1
print("Initial State")
print_state(p,q,turn)
run_num = int(math.pow(10,4))

if input == 0:
    for i in range(1,run_num):
        p,q,turn = next_state_p(p,q,turn)
        p,q,turn = next_state_q(p,q,turn)

if input == 1:
    for i in range(1,run_num):
        p,q,turn = next_state_q(p,q,turn)
        p,q,turn = next_state_p(p,q,turn)

if input == 2:
    for i in range(1,run_num):
        p,q,turn = next_state_q(p,q,turn)
        p,q,turn = next_state_q(p,q,turn)
        p,q,turn = next_state_p(p,q,turn)
        p,q,turn = next_state_p(p,q,turn)

if input == 3:
    for i in range(1,run_num):
        p,q,turn = next_state_q(p,q,turn)

if input == 4:
    for i in range(1,run_num):
        p,q,turn = next_state_p(p,q,turn)

