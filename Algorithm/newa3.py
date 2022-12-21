import numpy as np
import scipy
import pandas as pd
from scipy.stats import binom
import random
import meanshift
import unit
import math
from sklearn.cluster import MeanShift
import algorithm2
import operator

def CalModel(datas,cluster_gazes,l=3,ld=3):
    gaze = []
    ope = []
    opemap = []
    gazemap = []
    gazemap_list = []
    ret = [[[],[],i]for i in range(16)]
    l_datas = len(datas)
    for i in range(l_datas):
        if datas[i][8]!=-1 and (datas[i-1][6]!=datas[i][6] or datas[i-1][7]!=datas[i][7]):
            idx = cluster_gazes.predict([[datas[i][6],datas[i][7]]])[0]
            if len(gaze)==0 or gaze[-1][0]!=idx:
                d = [idx,datas[i][8]]
                gaze.append(d)
            elif gaze[-1][0]==idx:
                gaze[-1][1] += datas[i][8]
        if datas[i][9]!=-1:
            SID = datas[i][9]
            WID = datas[i][10]
            ID = int(SID * 8 + WID)
            if len(ope) > 0:
                cm = ""
                for j in range(max(0,len(ope) - ld),len(ope)):
                    cm += str(ope[j])
                if cm not in opemap:
                    opemap.append(cm)
                ret[ID][0].append(opemap.index(cm))
            new_gaze = []
            if len(gaze)>=l:
                new_gaze = gaze[len(gaze)-l:len(gaze)]
            elif len(gaze)<l and len(gaze)>0:
                num = len(gaze)
                for j in gaze:
                    new_gaze.append(j)
                while num<l:
                    mx = -1
                    idx = -1
                    for j in range(num):
                        if new_gaze[j][1]>mx:
                            mx = new_gaze[j][1]
                            idx = j
                    up_gaze = []
                    for j in range(num):
                        if j == idx:
                            up_gaze.append([new_gaze[j][0],new_gaze[j][1]/2])
                            up_gaze.append([new_gaze[j][0],new_gaze[j][1]/2])
                        else:
                            up_gaze.append([new_gaze[j][0], new_gaze[j][1]])
                    new_gaze.clear()
                    for j in up_gaze:
                        new_gaze.append(j)
                    num = len(new_gaze)
            if len(new_gaze)>0:
                gm = ""
                for j in new_gaze:
                    gm+=str(j[0])
                if gm not in gazemap:
                    gazemap.append(gm)
                    d = []
                    for j in new_gaze:
                        d.append(j[0])
                    gazemap_list.append(d)
                ret[ID][1].append(gazemap.index(gm))
            gaze.clear()
            #if len(ope)==0 or ope[-1]!=ID:
            # if len(ope) == 0 or ID != ope[-1] or ope[-1] != 10:
            #     ope.append(ID)
            ope.append(ID)
    return ret,opemap,gazemap,gazemap_list
'''
datas:[[click_0,click_1,...,click_l],[gaze_0,...,gaze_l],click_2]
'''
def bys(datas,l_ope,l_gaze,l_click,ll=3,ld=3):
    P = [0 for i in range(l_click)]
    click = [[0 for j in range(l_ope)] for i in range(l_click) ]
    gaze = [[0 for j in range(l_gaze)]for i in range(l_click) ]
    l = len(datas)
    for i in range(l):

        P[datas[i][2]] += 1
        for j in datas[i][0]:
            click[datas[i][2]][j] += 1
        for j in datas[i][1]:
            gaze[datas[i][2]][j] += 1
    for i in range(l_click):
        P[i] /= l
        sum = 0
        for k in range(l_ope):
            sum += click[i][k]
        if sum:
            for k in range(l_ope):
                click[i][k] /= sum
        sum = 0
        for k in range(l_gaze):
            sum += gaze[i][k]
        if sum:
            for k in range(l_gaze):
                gaze[i][k] /= sum
    return P, click, gaze
'''
lt:[[click_0,click_1,...,click_l],[gaze_0,...,gaze_l]]
'''
def DTW(a,b,gaze):
    la = len(a)
    lb = len(b)
    if len(b[0]) > 1:
        newb = []
        for i in b:
            newb.append(i[0])
        b = newb
    dis = [[0 for i in range(lb)]for j in range(la)]
    dp = [[(1<<30) for i in range(lb)]for j in range(la)]
    for i in range(la):
        for j in range(lb):
            l = 2
            d = 0
            for k in range(l):
                d += (gaze[a[i]][k]-gaze[b[j]][k])**2
            d = math.sqrt(d)
            dis[i][j] = d
    dp[0][0] = dis[0][0]
    for i in range(la):
        for j in range(lb):
            if i:
                dp[i][j] = min(dp[i][j],dp[i-1][j]+dis[i][j])
            if j:
                dp[i][j] = min(dp[i][j],dp[i][j-1]+dis[i][j])
            if i and j:
                dp[i][j] = min(dp[i][j], dp[i-1][j - 1] + dis[i][j])
    return dp[la-1][lb-1]

def bys_predict(P,click,gaze,lt,opemap,gazemap,gazemap_list,gaze_d,mode,ll=3):
    l = len(P)
    ret = [0 for i in range(l)]
    cm = ""
    gm = ""
    for i in lt[0]:
        cm += str(i)
    for i in lt[1]:
        gm += str(i[0])
    #print(cm)
    if cm in opemap:
        mn = (1<<30)
        idx = -1
        for i in range(len(gazemap_list)):
            rr = DTW(gazemap_list[i],lt[1],gaze_d)
            if rr < mn:
                mn = rr
                idx = i
        for i in range(l):
            ret[i] = P[i] * gaze[i][idx]*click[i][opemap.index(cm)]
        #print(cm)
        #print(ret)
    return ret
def solve(gaze_list,ll):
    if len(gaze_list)>=ll:
        return gaze_list[len(gaze_list)-ll:len(gaze_list)]
    else:
        num = len(gaze_list)
        new_gaze= []
        for j in gaze_list:
            new_gaze.append(j)
        while num < ll:
            mx = -1
            idx = -1
            for j in range(num):
                if new_gaze[j][1] > mx:
                    mx = new_gaze[j][1]
                    idx = j
            up_gaze = []
            for j in range(num):
                if j == idx:
                    up_gaze.append([new_gaze[j][0], new_gaze[j][1] / 2])
                    up_gaze.append([new_gaze[j][0], new_gaze[j][1] / 2])
                else:
                    up_gaze.append([new_gaze[j][0], new_gaze[j][1]])
            new_gaze.clear()
            for j in up_gaze:
                new_gaze.append(j)
            num = len(new_gaze)
        return new_gaze

def ys(idx):
    if idx<8:
        return 0,int(idx)
    else:
        return 1,int(idx-8)
#def cal(lt,cluster_gazes,Amean,P,click_P,gaze_P,times = 10,ll=3):
def cal(lt,cluster_gazes,Amean,P,click_P,gaze_P,opemap, gazemap, gazemap_list,gaze_d,mode,times = 10,ll=3,ld=3):
    ret = []
    ope_list = []
    gaze_list = []
    ql = [[0, 0] for i in range(times)]
    click_move = [[0, 0] for i in range(times)]
    now = 0
    my_list = []
    cnt = 0
    lst_SID = -1
    lst_WID = -1
    lst_FX = -1
    lst_FY = -1
    lst_gaze_x = -1
    lst_gaze_y = -1
    ll_gaze_x = -1
    ll_gaze_y = -1
    flag_1 = 0
    last_click = 3
    for i in lt:
        #print(cnt,len(lt))
        cnt+=1
        ret_d = i
        ql[now][0] = i[1]
        ql[now][1] = i[2]
        click_move[now][0] = i[3]
        click_move[now][1] = i[4]
        now = (now + 1) % times
        d, dd = algorithm2.adway(ql, click_move, times)
        if i[9]!=-1:
            ID = int(i[9]*8+i[10])
            #if len(ope_list)==0:
            #if len(ope_list)==0 or ope_list[-1]!=ID:
            ope_list.append(ID)
            # if len(ope_list)==0 or ID != ope_list[-1] or ope_list[-1]!=10:
            #     ope_list.append(ID)
        if i[8]!=-1 and (lst_FX!=i[6] or lst_FY!=i[7]):
            bgaze = cluster_gazes.predict([[i[6],i[7]]])[0]
            if len(gaze_list)==0 or gaze_list[-1][0]!=bgaze:
                gaze_list.append([bgaze,i[8]])
            elif gaze_list[-1][0]==bgaze:
                gaze_list[-1][1]+=i[8]
            lst_FX = i[6]
            lst_FY = i[7]
        last_click = i[5]
        if i[8] != 1 and (lst_gaze_x != i[6] or lst_gaze_y != i[7]):
            ll_gaze_x = lst_gaze_x
            ll_gaze_y = lst_gaze_y
            lst_gaze_x = i[6]
            lst_gaze_y = i[7]
            flag_1 = 1
        if dd < 20 and i[8] != -1 and ((ll_gaze_x - i[6]) ** 2 + (ll_gaze_y - i[7]) ** 2 > 10000 or (
                lst_gaze_x == i[6] and lst_gaze_y == i[7])) and flag_1 == 1:
            flag_1 = 0
            #print(ll)
            if len(ope_list)>ld and len(gaze_list)>0:
                ga = solve(gaze_list,ll)
                P_now = bys_predict(P,click_P,gaze_P,[ope_list[len(ope_list)-ld:len(ope_list)],ga],opemap, gazemap, gazemap_list, gaze_d,mode,ll=ll)
                #P_now = bys_predict(P,click_P,gaze_P,[ope_list[len(ope_list)-ll:len(ope_list)],ga])
                idx = -1
                mx = 0
                l = len(P_now)
                for j in range(l):
                    if P_now[j]>mx:
                        mx = P_now[j]
                        idx = j
                if idx!=-1:
                    SID,WID = ys(idx)
                    if SID!=lst_SID or WID!=lst_WID:
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
                ret_d.append(0)
                ret_d.append(i[6])
                ret_d.append(i[7])
        else:
            ret_d.append(-1)
            ret_d.append(-1)
            ret_d.append(-1)
        if i[9]!=-1:
            gaze_list.clear()
        ret.append(ret_d)
    return ret
