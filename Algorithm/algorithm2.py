import math
import algorithm1
import heb
import unit
import operator
import meanshift
from sklearn.cluster import MeanShift
import washdata
def single_cluster(gaze):
    clustering = MeanShift(bandwidth=20).fit(gaze)
    cluster_ = clustering.labels_
    cluster_gaze, d = meanshift.cal_MandD_list(gaze, cluster_, len(gaze))
    return clustering,cluster_gaze

def DTW(a,b,gaze):
    la = len(a)
    lb = len(b)
    if len(a[0])>1:
        newa = []
        for i in a:
            newa.append(i[0])
        a = newa
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
            # print(gaze)
            # print(a[i])
            # print(b[j])
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

def CalGazeModel(datas,cluster_gazes,l=3):
    gaze = []
    ret = [[[]for i in range(8)],[[]for i in range(8)]]
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
            new_gaze = []
            new_gaze_list = []
            if len(gaze)>=l:
                for i in range(len(gaze)-l,len(gaze)-l+1):
                    new_gaze_list = gaze[i:i+l]
                    ok = 1
                    for j in ret[int(SID)][int(WID)]:
                        if operator.eq(new_gaze_list, j) == True:
                            ok = 0
                            break
                    if ok:
                        ret[int(SID)][int(WID)].append(new_gaze_list)
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
                ok = 1
                for j in ret[int(SID)][int(WID)]:
                    if operator.eq(new_gaze,j)==True:
                        ok = 0
                        break
                if ok:
                    ret[int(SID)][int(WID)].append(new_gaze)
            gaze.clear()
    return ret

def CalOpeModel(datas, l=3):
    ope = []
    ret = [[[]for i in range(8)],[[]for i in range(8)]]
    l_datas = len(datas)
    for i in range(l_datas):
        if datas[i][9]!=-1:
            SID = datas[i][9]
            WID = datas[i][10]
            cm = ""
            for j in range(max(0,len(ope)-l),len(ope)):
                cm += ope[j]
            if cm not in ret[int(SID)][int(WID)] and cm!="":
                ret[int(SID)][int(WID)].append(cm)
            ID = str(int(SID))+str(int(WID))
            # if len(ope)==0 or ope[-1]!=ID:
            #     d = ID
            #     ope.append(d)
            ope.append(ID)
    return ret

def adway(ql,click_move,times):
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
        dd += unit.get_dis([click_x, click_y], [click_move[j][0], click_move[j][1]])**2
    d /= times
    dd /= times
    dd = math.sqrt(dd)
    return d, dd

def solve(ope_list,gaze_list,gazemodel,opemodel,ll,gaze):
    idx = [-1,-1]
    if len(gaze_list)==0:
        return idx
    if len(ope_list)==0 or len(gaze_list)==0:
        return idx
    firstnum = [[],[]]
    cm = ""
    # for j in range(max(0, len(ope_list) - ll), len(ope_list)):
    #     cm += str(int(ope_list[j][0])) + str(int(ope_list[j][1]))
    #
    # for k in range(2):
    #     for i in range(len(opemodel[k])):
    #         if cm in opemodel[k][i]:
    #             firstnum[k].append(i)

    mn = (1<<30)
    for k in range(2):
        for i in range(8):
                for j in gazemodel[k][i]:
                    nv = DTW(gaze_list[max(0,len(gaze_list)-ll):len(gaze_list)],j,gaze)
                    if nv<mn:
                        mn = nv
                        idx[0] = k
                        idx[1] = i
    # for k in range(2):
    #     for i in firstnum[k]:
    #         for j in gazemodel[k][i]:
    #             nv = DTW(gaze_list[max(0,len(gaze_list)-ll):len(gaze_list)],j,gaze)
    #             if nv<mn:
    #                 mn = nv
    #                 idx[0] = k
    #                 idx[1] = i
    #print(mn)
    return idx

def single_predict(data_test, gaze,cluster_gazes, Amean , gazemodel,opemodel,l=3, times=30):
    ope_list = []
    gaze_list = []
    ql = [[0, 0] for i in range(times)]
    click_move = [[0, 0] for i in range(times)]
    now = 0
    my_list = []
    lst_SID = -1
    lst_WID = -1
    lst_gaze_x = -1
    lst_gaze_y = -1
    ll_gaze_x = -1
    ll_gaze_y = -1
    lst_FX = -1
    lst_FY = -1
    flag_1 = 0
    for i in data_test:
        #print(cnt,len(data_test))
        ret_d = i
        ql[now][0] = i[1]
        ql[now][1] = i[2]
        click_move[now][0] = i[3]
        click_move[now][1] = i[4]
        now = (now + 1) % times
        d,dd = adway(ql,click_move,times)
        if i[9]!=-1:
            ope_list.append([i[9],i[10]])
        if i[8]!=-1 and (lst_FX!=i[6] or lst_FY!=i[7]):
            bgaze = cluster_gazes.predict([[i[6],i[7]]])[0]
            if len(gaze_list)==0 or gaze_list[-1][0]!=bgaze:
                gaze_list.append([bgaze,i[8]])
            elif gaze_list[-1][0]==bgaze:
                gaze_list[-1][1]+=i[8]
            lst_FX = i[6]
            lst_FY = i[7]
        if i[8]!=1 and (lst_gaze_x!=i[6] or lst_gaze_y!=i[7]):
            ll_gaze_x = lst_gaze_x
            ll_gaze_y = lst_gaze_y
            lst_gaze_x = i[6]
            lst_gaze_y = i[7]
            flag_1 = 1
        if dd<20 and i[8]!=-1 and ((ll_gaze_x-i[6])**2+(ll_gaze_y-i[7])**2>10000 or (lst_gaze_x==i[6]and lst_gaze_y==i[7])) and flag_1==1:
            idx = solve(ope_list, gaze_list, gazemodel, opemodel, l, gaze)
            #print(idx)
            SID = -1
            WID = -1
            cc = washdata.calarea([i[3],i[4]])
            if idx[0] != -1:
                if (idx[0]!=lst_SID or idx[1]!=lst_WID) and (idx[0]!=cc[0] or idx[1]!=cc[1]): #and (idx[0]!=i[9] or idx[1]!=i[10]): #and unit.get_dis([i[3],i[4]],[Amean[idx[0]][idx[1]][0],Amean[idx[0]][idx[1]][1]])>10:
                    ret_d.append(1)
                else:
                    ret_d.append(0)
                ret_d.append(Amean[idx[0]][idx[1]][0])
                ret_d.append(Amean[idx[0]][idx[1]][1])
                lst_SID=idx[0]
                lst_WID=idx[1]
            else:
                ret_d.append(0)
                ret_d.append(i[6])
                ret_d.append(i[7])
            flag_1 = 0
        else:
            ret_d.append(-1)
            ret_d.append(-1)
            ret_d.append(-1)

        my_list.append(ret_d)
        if i[9] != -1:
            gaze_list.clear()
    return my_list

