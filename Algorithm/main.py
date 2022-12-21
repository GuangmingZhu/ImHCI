import numpy as np
import pandas as pd
MIN_DISTANCE = 0.000001  # mini error

import os
import algorithm1
import algorithm2
import newa3

def calmean(datas):
    ret = [[[0,0] for i in range(8)],[[0,0] for j in range(8)]]
    num = [[0 for i in range(8)], [0 for j in range(8)]]
    gaze = [[[] for i in range(8)],[[] for j in range(8)]]
    l = len(datas)
    for i in range(l):
        if datas[i][9] != -1:
            ret[int(datas[i][9])][int(datas[i][10])][0] += datas[i][3]
            ret[int(datas[i][9])][int(datas[i][10])][1] += datas[i][4]
            num[int(datas[i][9])][int(datas[i][10])] += 1
            if datas[i][8] != -1:
                gaze[int(datas[i][9])][int(datas[i][10])].append([datas[i][6],datas[i][7]])
            else:
                gaze[int(datas[i][9])][int(datas[i][10])].append([datas[i][1],datas[i][2]])
    for i in range(8):
        if num[0][i]:
            ret[0][i][0] /= num[0][i]
            ret[0][i][1] /= num[0][i]
    for i in range(8):
        if num[1][i]:
            ret[1][i][0] /= num[1][i]
            ret[1][i][1] /= num[1][i]
    return ret,num,gaze

if __name__ == '__main__':
    all_num = [["02","03","11","13","14"],["04","08","15","16","21"],["05", "07", "09", "17","19"],["06","10","12","20","18"]]
    Sens = ["S01","S02","S03","S04"]

    Logic = ["L01","L02","L03","l04","L05","L06","L07"]

    for llen in range(3,4):
        for Sen in Sens:
            print("now S:"+Sen)
            for i in range(len(all_num)):
                num_train = []
                num_test = all_num[i]
                for j in range(len(all_num)):
                    if i!=j:
                        for k in all_num[j]:
                            num_train.append(k)
                train_data = []
                for j in num_train:
                    filenames = os.listdir("newdata/" + j + "/")
                    for filename in filenames:
                        if Sen not in filename:
                            continue
                        datas = np.loadtxt(open("newdata/" + j + "/" + filename, "rb"), delimiter=",", skiprows=1)
                        datas = datas.tolist()
                        for k in datas:
                            train_data.append(k)
                Amean,Anum,gazelist = calmean(train_data)


                print("strart a1")
                gaze_clu,gaze_clu_d = algorithm1.single_cluster(gazelist)
                for j in num_test:
                    test_data = []
                    filenames = os.listdir("nor2data/" + j + "/")
                    for filename in filenames:
                        if Sen not in filename:
                            continue
                        datas = np.loadtxt(open("nor2data/" + j + "/" + filename, "rb"), delimiter=",", skiprows=1)
                        datas = datas.tolist()
                        for k in datas:
                            test_data.append(k)
                    reslist = algorithm1.single_predict(test_data,gaze_clu_d,gaze_clu,Amean,times=30)
                    print(algorithm1.cal_acc(reslist))
                    dataframe = pd.DataFrame(test_data)
                    dataframe.to_csv("res/a1_10_"+Sen+"-"+j+"_"+str(llen)+".csv", index=False, sep=',')

                print("strart a2")
                lst_x = -1
                lst_y = -1
                all_gaze = []
                for j in train_data:
                    if j[8]!=-1 and (lst_x!=j[6] or lst_y!=j[7]):
                        all_gaze.append([j[6],j[7]])
                        lst_x = j[6]
                        lst_y = j[7]
                gaze_clu,gaze_clu_d =algorithm2.single_cluster(all_gaze)
                eyemode = algorithm2.CalGazeModel(train_data,gaze_clu,llen)
                opemode = algorithm2.CalOpeModel(train_data,llen)

                for j in num_test:
                    test_data = []
                    filenames = os.listdir("nor2data/" + j + "/")
                    #print(j + "的数值为:")
                    for filename in filenames:
                        if Sen not in filename:
                            continue
                        datas = np.loadtxt(open("nor2data/" + j + "/" + filename, "rb"), delimiter=",", skiprows=1)
                        datas = datas.tolist()
                        for k in datas:
                            test_data.append(k)
                    reslist = algorithm2.single_predict(test_data,gaze_clu_d,gaze_clu,Amean,eyemode,opemode,l=llen,times=30)
                    print(algorithm1.cal_acc(reslist))
                    dataframe = pd.DataFrame(test_data)
                    dataframe.to_csv("res/a2_"+Sen+"-"+j+"_"+str(llen)+".csv", index=False, sep=',')

                print("strart n3")
                lst_x = -1
                lst_y = -1
                all_gaze = []
                for j in train_data:
                    if j[8] != -1 and lst_x != j[6] and lst_y != j[7]:
                        all_gaze.append([j[6], j[7]])
                        lst_x = j[6]
                        lst_y = j[7]
                gaze_clu, gaze_clu_d = algorithm2.single_cluster(all_gaze)
                mode,opemap,gazemap,gazemap_list = newa3.CalModel(train_data, gaze_clu,l=llen)
                P, Pclick, Pgaze = newa3.bys(mode,len(opemap),len(gazemap),16,ll=llen)
                for j in num_test:
                    test_data = []
                    filenames = os.listdir("nor2data/" + j + "/")
                    for filename in filenames:
                        if Sen not in filename:
                            continue
                        datas = np.loadtxt(open("nor2data/" + j + "/" + filename, "rb"), delimiter=",", skiprows=1)
                        datas = datas.tolist()
                        for k in datas:
                            test_data.append(k)
                    reslist = newa3.cal(test_data,gaze_clu,Amean,P,Pclick,Pgaze,opemap,gazemap,gazemap_list,gaze_clu_d,mode,ll=llen,times=30)
                    print(algorithm1.cal_acc(reslist))
                    dataframe = pd.DataFrame(test_data)
                    dataframe.to_csv("res/main0nann3_"+Sen+"-"+j+"_"+str(llen)+".csv", index=False, sep=',')


