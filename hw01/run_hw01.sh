#!/bin/bash
echo "Run Python and save output"
python hw01.py 0 > pq.txt
python hw01.py 1 > qp.txt
python hw01.py 2 > qqpp.txt
python hw01.py 3 > q.txt
python hw01.py 4 > p.txt

echo "0 is a  good thing for the Mutual Exclusion and Deadlock"
echo "Check for Mutual Exclusion in pq"
grep "No Mutual" pq.txt | wc -l

echo "Check for Mutual Exclusion in qp"
grep "No Mutual" qp.txt | wc -l

echo "Check for Mutual Exclusion in qqpp"
grep "No Mutual" qqpp.txt | wc -l

echo "Check for Mutual Exclusion in p"
grep "No Mutual" p.txt | wc -l

echo "Check for Mutual Exclusion in q"
grep "No Mutual" q.txt | wc -l

echo "Check for Deadlock in pq"
grep "Deadlock" pq.txt | wc -l

echo "Check for Deadlock in qp"
grep "Deadlock" qp.txt | wc -l

echo "Check for Deadlock in qqpp"
grep "Deadlock" qqpp.txt | wc -l

echo "Check for Deadlock in p"
grep "Deadlock" p.txt | wc -l

echo "Check for Deadlock in q"
grep "Deadlock" q.txt | wc -l

echo "0 is a bad thing for Starvation"
echo "Check for Starvation in pq"
echo "Does P ever hit CS?"
grep "P in CS = True" pq.txt | wc -l
echo "Does Q ever hit CS?"
grep "Q in CS = True" pq.txt | wc -l

echo "Check for Starvation in qp"
echo "Does P ever hit CS?"
grep "P in CS = True" qp.txt | wc -l
echo "Does Q ever hit CS?"
grep "Q in CS = True" qp.txt | wc -l

echo "Check for Starvation in qqpp"
echo "Does P ever hit CS?"
grep "P in CS = True" qqpp.txt | wc -l
echo "Does Q ever hit CS?"
grep "Q in CS = True" qqpp.txt | wc -l

echo "To provide a case where starvation happens I have included p and q separately" 
echo "Here 0 is showcased as only 1 process ever runs"
echo "Check for Starvation in p"
echo "Does Q ever hit CS?"
grep "Q in CS = True" p.txt | wc -l

echo "Check for Starvation in q"
echo "Does P ever hit CS?"
grep "P in CS = True" q.txt | wc -l


