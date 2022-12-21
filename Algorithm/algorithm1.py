import csv
import math
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from numpy import loadtxt
from pandas import read_csv
MIN_DISTANCE = 0.000001  # mini error
import matplotlib.colors as colors
import  math
from numpy import unique
from numpy import where
from sklearn.datasets import make_classification
from sklearn.mixture import GaussianMixture
import meanshift
import  unit
from sklearn.cluster import MeanShift
import washdata

def single_cluster(gaze):
    ret = [[],[]]
    cluster_gazes = [[],[]]
    for i in range(8):
        if len(gaze[0][i])==0:
            gaze[0][i].append([0,0])
        clustering = MeanShift(bandwidth=20).fit(gaze[0][i])
        cluster_ = clustering.labels_
        cluster_gaze, d = meanshift.cal_MandD_list(gaze[0][i], cluster_, len(gaze[0][i]))
        ret[0].append(clustering)
        cluster_gazes[0].append(cluster_gaze)
    for i in range(8):
        if len(gaze[1][i])==0:
            gaze[1][i].append([0,0])
        clustering = MeanShift(bandwidth=20).fit(gaze[1][i])
        cluster_ = clustering.labels_
        cluster_gaze, d = meanshift.cal_MandD_list(gaze[1][i], cluster_, len(gaze[1][i]))
        ret[1].append(clustering)
        cluster_gazes[1].append(cluster_gaze)
    return ret,cluster_gazes


def knlu(m,d,x):
    dis = (x[0]-m[0])**2+(x[1]-m[1])**2
    return math.exp(-dis/(2*((d+1)**2)))

def calP(P,gaze,cluster_gazes):
    SID = -1
    WID = -1
    ret_P = 0
    for i in range(2):
        for j in range(len(cluster_gazes[i])):
            lab = cluster_gazes[i][j].predict([P])[0]
            p = knlu([gaze[i][j][lab][0],gaze[i][j][lab][1]],gaze[i][j][lab][3],P)
            if p > ret_P:
                ret_P = p
                SID = i
                WID = j
    return SID,WID

def single_predict(data_test, gaze,cluster_gazes ,Amean,times = 30):
    ql = [[0, 0] for i in range(times)]
    click_move = [[0, 0] for i in range(times)]
    now = 0
    my_list = []
    lst_SID = -1
    lst_WID = -1
    cnt = 0
    lst_gaze_x = -1
    lst_gaze_y = -1
    ll_gaze_x = -1
    ll_gaze_y = -1
    flag_1 = 0
    for i in data_test:
        ret_d = i
        ql[now][0] = i[1]
        ql[now][1] = i[2]
        click_move[now][0] = i[3]
        click_move[now][1] = i[4]
        now = (now + 1) % times
        mx = 0
        click_x = 0
        click_y = 0
        my = 0
        for j in range(times):
            mx += ql[j][0]
            my += ql[j][1]
            click_x += click_move[j][0]
            click_y += click_move[j][1]
        mx /= times
        my /= times
        click_x /= times
        click_y /= times
        d = 0
        dd = 0
        for j in range(times):
            d += math.sqrt((ql[j][0] - mx) ** 2 + (ql[j][1] - my) ** 2)
            dd += unit.get_dis([click_x,click_y],[click_move[j][0],click_move[j][1]])**2
        d /= times
        dd /= times
        dd = math.sqrt(dd)
        if i[8] != 1 and (lst_gaze_x != i[6] or lst_gaze_y != i[7]):
            ll_gaze_x = lst_gaze_x
            ll_gaze_y = lst_gaze_y
            lst_gaze_x = i[6]
            lst_gaze_y = i[7]
            flag_1 = 1
        if dd < 20 and i[8] != -1 and ((ll_gaze_x - i[6]) ** 2 + (ll_gaze_y - i[7]) ** 2 > 10000 or (
                lst_gaze_x == i[6] and lst_gaze_y == i[7])) and flag_1 == 1:
            SID, WID = calP([i[6], i[7]], gaze, cluster_gazes)
            flag_1 = 0
            if SID != -1:
                if lst_SID != SID or lst_WID!=WID:
                    ret_d.append(1)
                else:
                    ret_d.append(0)
                ret_d.append(Amean[SID][WID][0])
                ret_d.append(Amean[SID][WID][1])
                lst_SID = SID
                lst_WID = WID
            else:
                ret_d.append(0)
                ret_d.append(i[6])
                ret_d.append(i[7])
        else:
            ret_d.append(-1)
            ret_d.append(-1)
            ret_d.append(-1)
        ret_d.append(dd)
        my_list.append(ret_d)

    return my_list
position = [
    [421,608,1],
    [1694,606,2],
    [412,966,3],
    [850,965,4],
    [1238,972,5],
    [1700,970,6]
]
w = 90
h = 40
def nxtpd(P):
    P[0]=P[0]-1920
    l = len(position)
    for i in range(l):
        if position[i][0] <= P[0] and P[0]<=position[i][0]+w and position[i][1]<=P[1] and P[1]<=position[i][1]+h:
            return i
    return -1
def cal_acc(lt):
    lx,ly = 0,0
    dis = 0
    good_dis = 0
    error_dis = 0
    l = len(lt)
    alljumpnum = 0
    alljumpreal = 0
    acc = 0
    acc_num = 0
    acc_nxt = 0
    all_nxt = 0
    nxt_pd = 0
    l_0 = 0
    cnt_1 = 0
    cnt_2 = 0
    cnt_3 = 0
    cnt_4 = 0
    ccc = 0
    qyldj = 0
    num_nxt = 0
    lst_SID = -1
    lst_WID = -1
    yc = []
    opelist = []
    l_lt = len(lt)
    flag = [0 for i in range(l_lt)]
    big_d = 0
    for i in range(l):
        dis += unit.get_dis([lx,ly],[lt[i][3],lt[i][4]])
        lx,ly = lt[i][3],lt[i][4]
        if lt[i][5] == 0 and lt[i][9] != -1:
            for j in yc:
                ret1 = washdata.calarea(j)
                if (ret1[0] == lt[i][9] and ret1[1] == lt[i][10]) or (ret1[0] == 0 and lt[i][9] == 0):
                    cnt_3 += 1
            yc.clear()
        if lt[i][11] != -1 and (lt[i][12]!=lt[i-1][12] or lt[i][13]!=lt[i-1][13]):
            cnt_2+=1
            yc.append([lt[i][12],lt[i][13]])
        S,W,B = 0,0,0
        if lt[i][5] == 0 and lt[i][9]!= -1:
            opelist.append([lt[i][9],lt[i][10]])
            cnt_1 += 1
            flag_1 = -1
            flag_2 = -1
            if lst_SID != lt[i][9] or lst_WID != lt[i][10]:
                all_nxt += 1
            for j in range(l_0,i):
                if lt[j][11]!=-1:
                    ret1 = washdata.calarea([lt[j][12],lt[j][13]])
                    if lt[j][11] == 1:
                        if flag[j] == 0:
                            flag[j] = 1
                            alljumpnum += 1
                            if (ret1[0]==lt[i][9] and ret1[1]==lt[i][10]) or (ret1[0]==0 and lt[i][9]==0):
                                alljumpreal += 1
                        if flag_1!=-1:
                            if lt[flag_1][12] != lt[j][12] or lt[flag_1][13]!=lt[j][13]:
                                flag_1 = j
                        else:
                            flag_1 = j
                    if lt[j][11] != -1:
                        if flag_2!=-1:
                            if lt[flag_2][12] != lt[j][12] or lt[flag_2][13]!=lt[j][13]:
                                flag_2 = j
                        else:
                            flag_2 = j
            if flag_2 != -1:
                acc_num+=1
                a = [lt[flag_2][12],lt[flag_2][13]]
                ret1 = washdata.calarea(a)
                ret2 = washdata.calarea([lt[i][3],lt[i][4]])
                if (ret1[0]==ret2[0] and ret1[1]==ret2[1]) or (ret1[0]==ret2[0] and ret1[0]==0):
                    acc+=1
            if flag_1 != -1:
                #if lst_SID != lt[i][9] or lst_WID != lt[i][10]:
                num_nxt += 1
                dd = 0
                for j in range(flag_1,i):
                    dd += unit.get_dis([lt[j-1][3],lt[j-1][4]],[lt[j][3],lt[j][4]])
                a = [lt[flag_1][12],lt[flag_1][13]]
                c = unit.get_dis(a,[lt[i][3],lt[i][4]])
                #print(a,[lt[i][3],lt[i][4]])
                ret1 = washdata.calarea(a)
                ret2 = washdata.calarea([lt[i][3],lt[i][4]])
                if ret1[0]==ret2[0] and ret1[1]==ret2[1] or (ret1[0]==ret2[0] and ret1[0]==0):
                    #if lst_SID != lt[i][9] or lst_WID != lt[i][10]:
                    acc_nxt += 1
                    for j in range(l_0, i):
                        big_d += unit.get_dis([lt[j][3], lt[j][4]], [lt[j + 1][3], lt[j + 1][4]])
                # else:
                #     print("Wrong:")
                #     print(ret1,ret2)
                #     print(opelist[max(0,len(opelist)-3):len(opelist)])
                #     print(washdata.calarea([lt[i][1],lt[i][2]]))
                #else:
                 #   print(int(lt[i][9]),int(lt[i][10]),int(ret1[0]),int(ret1[1]))
                dd -= c
                error_dis += c
                good_dis+=dd
                big_d -= c
                    #print(lt[i][3],lt[i][4],lt[flag_1][12],lt[flag_1][13])
                nxt_pd = 0
            lst_SID = lt[i][9]
            lst_WID = lt[i][10]
            l_0 = i
        if nxtpd([lt[i][3],lt[i][4]])!=-1 and lt[i][5]==0:
            ccc+=1
        if lt[i][5]==0:
            qyldj += 1
    return alljumpreal,alljumpnum,acc_nxt,num_nxt,all_nxt,acc,acc_num,dis,good_dis,big_d,cnt_1,cnt_2,cnt_3,qyldj,ccc