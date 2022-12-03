import numpy as np
from typing import Callable, List

File_object = open("Calculations.txt", "w")
def func (x):
    return ( 110 * 3200 / x[0] + 0.5 * 150 * x[0]) + ( 150 * 2100 / x[1] + 0.5 * 260 * x[1]) + ( 120 * 5400 / x[2] + 0.5 * 240 * x[2]) + ( 130 * 7900 / x[3] + 0.5 * 200 * x[3]) + ( 100 * 2420 / x[4] + 0.5 * 230 * x[4])
    # return 4*pow((x[0]-5),2)+pow((x[1]-6),2)

def best_samples(func: Callable[[np.array], float], x0, M: int, N: int,  t, R, b):
    x = x0
    k = 0
    while k < N:
        y_ = []
        f = []
        print("\nИтерация: {}".format(k))
        for _ in range(M):
            e = np.random.uniform(-1, 1, len(x))
            y = x + t * e / np.linalg.norm(e)
            y_.append(y)
            f.append(func(y))
        print("\nЗначение координат случайных векторов: {}".format(f))
        File_object.write("\nЗначение координат случайных векторов: {}\n".format(f))
        
        min_index = np.argmin(f)
        f_min = f[min_index]
        print("Минимальное значение Y: {}".format(f_min))
        File_object.write("Минимальное значение Y: {}\n".format(f_min))

        if f_min < func(x):
            print("\n{} < {}".format(f_min,func(x)))
            x = y_[min_index]
            k += 1
            print("ШАГ УДАЧЕН!\nПереопределяем X: {}".format(x))
            File_object.write("ШАГ УДАЧЕН!\nПереопределяем X: {}\n".format(x))
        else:
            print("\nПроверяем условия окончания расчета\n{} > {}".format(f_min,func(x)))
            File_object.write("\nПроверяем условия окончания расчета\n{} > {}\n".format(f_min,func(x)))
            if t <= R:
                print("{} <= {}".format(t,R))
                File_object.write("{} <= {}\n".format(t,R))
                print("\n-----------Окончание расчета--------")
                File_object.write("\n-----------Окончание расчета--------\n")
                return x
            elif t > R:
                print("\n{} > {}".format(t,R))
                t *= b
                print("Меняем величину шага в соотвествии с коэффициентом сжатия: {}".format(t))
                File_object.write("Меняем величину шага в соотвествии с коэффициентом сжатия: {}\n".format(t))

    return x
x1,x2,x3,x4,x5 = best_samples(func,[50, 50, 50, 50, 50],20,100,1,0.00001,0.1)
x_ = [x1,x2,x3,x4,x5]
print("\nХ1 = {};\nX2 = {}\nX3 = {}\nX4 = {}\nX5 = {}\nY = {}".format(x1,x2,x3,x4,x5,func(x_)))
File_object.close()