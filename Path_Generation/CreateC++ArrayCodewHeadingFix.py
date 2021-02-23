#int x[3][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};
import csv
import os

inputfile = input("File: ")
with open(inputfile+'_left.csv', 'rU') as csvfile:

    csvstr = str(csvfile.name)
    
    f= open(csvstr[:-4]+".txt","w+")
    
    readCSV = csv.reader(csvfile, delimiter=',')
    row_count = sum(1 for row in readCSV)

    csvfile.seek(0)
    next(readCSV)

    f.write("double "+ csvstr[:-4]+" ["+str(row_count-1)+"] [4] = {")
    
    for ct, row in enumerate(readCSV):
        #Heading Conversion#
        raw_heading = float(row[3])
        deg_heading = raw_heading*180/3.145359
        
    
        if deg_heading > 180:
            deg_heading2 = deg_heading - 360

        else:
            
            deg_heading2 = deg_heading
        if ct == 0:
            h_old = deg_heading2
            h_new = deg_heading2
            deg_heading_old = deg_heading2
            
        else:
            h_new = h_old + (deg_heading2 - deg_heading_old)
            deg_heading_old = deg_heading2
        print(deg_heading2)
        
        ######

        pos = float(row[1])*7000
        velo = float(row[2])*7000
        if row_count-2 == ct:
            f.write("{"+row[0]+","+str(pos)+","+str(velo)+","+str(h_new)+"}};")
        else:
            f.write("{"+row[0]+","+str(pos)+","+str(velo)+","+str(h_new)+"},")
        #print(row[0],row[1],row[2],)
            #print(str(h_new))
f.close() 
with open(inputfile+'_right.csv', 'rU') as csvfile:

    csvstr = str(csvfile.name)
    
    f= open(csvstr[:-4]+".txt","w+")
    
    readCSV = csv.reader(csvfile, delimiter=',')
    row_count = sum(1 for row in readCSV)

    csvfile.seek(0)
    next(readCSV)

    f.write("double "+ csvstr[:-4]+" ["+str(row_count)+"] [4] = {")
    
    for ct, row in enumerate(readCSV):
        #Heading Conversion#
        raw_heading = float(row[3])
        deg_heading = raw_heading*180/3.145359

        if deg_heading > 180:
            deg_heading = deg_heading - 360
            
        if ct == 0:
            h_old = deg_heading
            h_new = deg_heading
            deg_heading_old = deg_heading
            
        else:
            h_new = h_old + (deg_heading - deg_heading_old)
            deg_heading_old = deg_heading
        
        ######
        pos = float(row[1])*7000
        velo = float(row[2])*7000
        if row_count-2 == ct:
            f.write("{"+row[0]+","+str(pos)+","+str(velo)+","+str(h_new)+"}};")
        else:
            f.write("{"+row[0]+","+str(pos)+","+str(velo)+","+str(h_new)+"},")

f.close() 
