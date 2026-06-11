STEPS
1. TO COMPILE THE PROGRAMS
Use gcc filename.c -o filename

2. TO RUN 
Use ./filename 

3. OUTPUT

QUESTION 1: Cloud Job Scheduler - Max-Heap 

Input array: P = {42, 17, 93, 28, 65, 81, 54, 60, 99, 73, 88}
Job IDs assigned: A=42, B=17, C=93, D=28, E=65, F=81, G=54, H=60, I=99, J=73, K=88

--- Step 1: Initial Binary Tree (before heapify) ---
Heap Array: [A:42] [B:17] [C:93] [D:28] [E:65] [F:81] [G:54] [H:60] [I:99] [J:73] [K:88] 
Tree structure (index-based):
Level 0: [A:42] 
Level 1: [B:17] [C:93] 
Level 2: [D:28] [E:65] [F:81] [G:54] 
Level 3: [H:60] [I:99] [J:73] [K:88] 

--- Step 2: After Building Max-Heap ---
Heap Array: [I:99] [K:88] [C:93] [H:60] [J:73] [F:81] [G:54] [B:17] [D:28] [A:42] [E:65] 
Tree structure (index-based):
Level 0: [I:99] 
Level 1: [K:88] [C:93] 
Level 2: [H:60] [J:73] [F:81] [G:54] 
Level 3: [B:17] [D:28] [A:42] [E:65] 

--- Step 3: Insert Urgent Job (Priority 100, ID='L') ---
Heap Array: [L:100] [K:88] [I:99] [H:60] [J:73] [C:93] [G:54] [B:17] [D:28] [A:42] [E:65] [F:81] 
Tree structure (index-based):
Level 0: [L:100] 
Level 1: [K:88] [I:99] 
Level 2: [H:60] [J:73] [C:93] [G:54] 
Level 3: [B:17] [D:28] [A:42] [E:65] [F:81] 

--- Step 4: Remove Job with Priority 100 (Aborted) ---
Heap Array: [I:99] [K:88] [C:93] [H:60] [J:73] [F:81] [G:54] [B:17] [D:28] [A:42] [E:65] 
Tree structure (index-based):
Level 0: [I:99] 
Level 1: [K:88] [C:93] 
Level 2: [H:60] [J:73] [F:81] [G:54] 
Level 3: [B:17] [D:28] [A:42] [E:65] 



QUESTION 2: Smart Airport Security - Max-Heap Priority Queue 

Passengers and Risk Scores:
  Alice: 72
  Brian: 55
  Chen: 88
  Fatima: 63
  Noah: 41
  Sofia: 79

--- Step 1: Initial Binary Tree (before heapify) ---
Heap Array: [Alice:72] [Brian:55] [Chen:88] [Fatima:63] [Noah:41] [Sofia:79] 
Tree structure:
Level 0: [Alice:72] 
Level 1: [Brian:55] [Chen:88] 
Level 2: [Fatima:63] [Noah:41] [Sofia:79] 

--- Step 2: After Building Max-Heap ---
Heap Array: [Chen:88] [Fatima:63] [Sofia:79] [Brian:55] [Noah:41] [Alice:72] 
Tree structure:
Level 0: [Chen:88] 
Level 1: [Fatima:63] [Sofia:79] 
Level 2: [Brian:55] [Noah:41] [Alice:72] 

--- Step 3: Priority Queue Extraction (Screening Order) ---
Priority Queue - Screening Order (Highest Risk First):
  1. Chen (Risk Score: 88)
  2. Sofia (Risk Score: 79)
  3. Alice (Risk Score: 72)
  4. Fatima (Risk Score: 63)
  5. Brian (Risk Score: 55)
  6. Noah (Risk Score: 41)

--- Step 4: Insert New Passenger 'Zara' with Risk Score 98 ---
Heap Array: [Zara:98] [Fatima:63] [Chen:88] [Brian:55] [Noah:41] [Alice:72] [Sofia:79] 
Tree structure:
Level 0: [Zara:98] 
Level 1: [Fatima:63] [Chen:88] 
Level 2: [Brian:55] [Noah:41] [Alice:72] [Sofia:79] 

--- Step 5: Remove Passenger with Risk Score 98 (Cleared) ---
Heap Array: [Chen:88] [Fatima:63] [Sofia:79] [Brian:55] [Noah:41] [Alice:72] 
Tree structure:
Level 0: [Chen:88] 
Level 1: [Fatima:63] [Sofia:79] 
Level 2: [Brian:55] [Noah:41] [Alice:72] 



QUESTION 3: Fiber-Optic Network - Kruskal's MST

--- Adjacency Matrix (cost in millions $) ---
     A  B  C  D  E  F  G
 A   0  4  8  0  0  0  0
 B   4  0 11  8  0  0  0
 C   8 11  0  0  7  1  0
 D   0  8  0  0  2  0  9
 E   0  0  7  2  0  6 10
 F   0  0  1  0  6  0  2
 G   0  0  0  9 10  2  0

--- All Edges (sorted by cost) ---
  C-F : 1 million
  D-E : 2 million
  F-G : 2 million
  A-B : 4 million
  E-F : 6 million
  C-E : 7 million
  A-C : 8 million
  B-D : 8 million
  D-G : 9 million
  E-G : 10 million
  B-C : 11 million

--- Applying Kruskal's Algorithm ---
Edge            Cost($M)   Action    
----            --------   ------    
C-F            1          ADDED to MST
D-E            2          ADDED to MST
F-G            2          ADDED to MST
A-B            4          ADDED to MST
E-F            6          ADDED to MST
C-E            7          SKIPPED (creates cycle)
A-C            8          ADDED to MST

--- MST Result: Selected Fiber-Optic Links ---
  Hub C <---> Hub F : 1 million dollars
  Hub D <---> Hub E : 2 million dollars
  Hub F <---> Hub G : 2 million dollars
  Hub A <---> Hub B : 4 million dollars
  Hub E <---> Hub F : 6 million dollars
  Hub A <---> Hub C : 8 million dollars

Total Minimum Installation Cost: USD 23 million




QUESTION 4: Cyber Incident BFS Analysis 

Enterprise Communication Graph:
  WS1 <-> WS2: 8 min
  WS1 <-> WS3: 15 min
  WS1 <-> WS4: 5 min
  WS2 <-> WS5: 12 min
  WS3 <-> WS5: 7 min
  WS3 <-> WS6: 9 min
  WS4 <-> WS6: 11 min
  WS5 <-> WS7: 6 min
  WS6 <-> WS7: 14 min

Enter suspected compromised workstation (e.g., WS1, WS2, ...WS7): 
BFS traversal from WS1:
  Visiting: WS1 (Source / Suspected Breach Point)

Direct Neighbors (One-Hop Contacts) of WS1:
  Node     | Transfer Time (min)
  ---------|--------------------
  WS2      | 8 min
  WS3      | 15 min
  WS4      | 5 min

Highest Risk Contact Analysis:
  = WS3 has the highest data transfer time: 15 minutes
  = This workstation is at HIGHEST RISK of exposure and data breach propagation.


QUESTION 5: Banking Risk Propagation - Bellman-Ford

Transaction Network Edges:
  Branch A -> Branch B : cost/risk = 4
  Branch A -> Branch D : cost/risk = 16
  Branch B -> Branch C : cost/risk = 6
  Branch B -> Branch E : cost/risk = 7
  Branch C -> Branch G : cost/risk = 9
  Branch D -> Branch E : cost/risk = 3
  Branch E -> Branch F : cost/risk = 2
  Branch F -> Branch C : cost/risk = -3
  Branch F -> Branch G : cost/risk = 10
  Branch G -> Branch H : cost/risk = 13
  Branch D -> Branch H : cost/risk = 20

Note: Negative edge weights indicate exploitable or suspicious routes.

No negative-weight cycles detected. Network is stable.

--- Shortest Paths from Branch A ---
Branch     Min Cost     Path                
------     --------     ----                
B          4            A -> B
C          10           A -> B -> C
D          16           A -> D
E          11           A -> B -> E
F          13           A -> B -> E -> F
G          19           A -> B -> C -> G
H          32           A -> B -> C -> G -> H


