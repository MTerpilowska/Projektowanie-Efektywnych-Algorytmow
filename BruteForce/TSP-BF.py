import itertools
import datetime
import time
import csv

fw = open('test_atsp_out2.csv', 'w' , newline='') # plik do danych wyjsciowych
writer = csv.writer(fw)  

#writer.writerow('tsp_6_1.txt')
for m in range(100):
    with open('tsp_10.txt') as f:                   #czytanie danych z pliku
        s = [int(x) for x in f.readline().split()]
        matrix = []
        for line in f:
            matrix.append([int(x) for x in line.split()])


    start_time = datetime.datetime.now()   #pomiar czasu
    start = time.monotonic_ns()
    city = list(range(1,s[0]))

    minimum = 9999999999
    minimum_path = []

    paths = itertools.permutations(city)    # path przypisujemy listę wszystkich permutacji wierzcholkow - poza wierzcholkiem 0 - startowym
    for path in paths:                      
        sum = 0
        for y in range (s[0]-1):            # liczymy sume krawedzi dla kazdej mozliwej sciezki
            if y==0:
                sum = sum + matrix[0][path[y]]      
            else:
                sum = sum + matrix[path[y-1]][path[y]]
        sum = sum + matrix[path[y]][0]           
        if sum<minimum:                      # jesli wyliczona suma jest mniejsza niz minimum staje sie minimalnym cyklem 
            minimum = sum
            minimum_path = path
    end = time.monotonic_ns()        
    end_time = datetime.datetime.now()       # koniec pomiaru czasu
    time_diff = (end_time - start_time)
    timed = (end - start)

    execution_time = time_diff.total_seconds() * 1000
    exec_t = [execution_time]
    writer.writerow(exec_t)

    print(minimum, minimum_path, execution_time, timed)

    f.close() 

""""
writer.writerow('tsp_6_2.txt')
for m in range(100):
    with open('tsp_6_2.txt') as f:
        s = [int(x) for x in f.readline().split()]
        matrix = []
        for line in f:
            matrix.append([int(x) for x in line.split()])

    start_time = datetime.datetime.now()
    city = list(range(1,s[0]))

    minimum = 9999999999
    minimum_path = []

    paths = itertools.permutations(city)
    for path in paths:
        sum = 0
        for y in range (s[0]-1):
            if y==0:
                sum = sum + matrix[0][path[y]]
            else:
                sum = sum + matrix[path[y-1]][path[y]]
        sum = sum + matrix[path[y]][0]           
        if sum<minimum:
            minimum = sum
            minimum_path = path
    end_time = datetime.datetime.now()
    time_diff = (end_time - start_time)

    execution_time = time_diff.total_seconds() * 1000
    exec_t = [execution_time]
    writer.writerow(exec_t)

    f.close() 

writer.writerow('tsp_10.txt')
for m in range(10):
    with open('tsp_10.txt') as f:
        s = [int(x) for x in f.readline().split()]
        matrix = []
        for line in f:
            matrix.append([int(x) for x in line.split()])

    start_time = datetime.datetime.now()
    city = list(range(1,s[0]))

    minimum = 9999999999
    minimum_path = []

    paths = itertools.permutations(city)
    for path in paths:
        sum = 0
        for y in range (s[0]-1):
            if y==0:
                sum = sum + matrix[0][path[y]]
            else:
                sum = sum + matrix[path[y-1]][path[y]]
        sum = sum + matrix[path[y]][0]           
        if sum<minimum:
            minimum = sum
            minimum_path = path
    end_time = datetime.datetime.now()
    time_diff = (end_time - start_time)

    execution_time = time_diff.total_seconds() * 1000
    exec_t = [execution_time]
    writer.writerow(exec_t)

    f.close()    

writer.writerow('tsp_12.txt')
for m in range(3):
    with open('tsp_12.txt') as f:
        s = [int(x) for x in f.readline().split()]
        matrix = []
        for line in f:
            matrix.append([int(x) for x in line.split()])

    start_time = datetime.datetime.now()
    city = list(range(1,s[0]))

    minimum = 9999999999
    minimum_path = []

    paths = itertools.permutations(city)
    for path in paths:
        sum = 0
        for y in range (s[0]-1):
            if y==0:
                sum = sum + matrix[0][path[y]]
            else:
                sum = sum + matrix[path[y-1]][path[y]]
        sum = sum + matrix[path[y]][0]           
        if sum<minimum:
            minimum = sum
            minimum_path = path
    end_time = datetime.datetime.now()
    time_diff = (end_time - start_time)

    execution_time = time_diff.total_seconds() * 1000
    exec_t = [execution_time]
    writer.writerow(exec_t)

    f.close()          

"""

