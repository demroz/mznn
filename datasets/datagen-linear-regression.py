#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 13 14:18:52 2025

this script just generated some random data 
to play with for linear-regression

@author: mzhelyez
"""

import numpy as np
import pandas as pd
import scipy as sp
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
from datetime import datetime

NUMPTS = 1000

def generate_random_linear_2D(xmin, xmax, 
                              slope, intercept,
                              noisestd,
                              plot=False):
    x = np.linspace(xmin, xmax, NUMPTS)
    y = x * slope + intercept    
    noise = np.random.normal(loc=0.0, scale = noisestd, size =y.shape)
    noisy_y = y + noise
    
    reg = LinearRegression().fit(x.reshape(-1,1),noisy_y)
    r_sq = reg.score(x.reshape(-1,1), y)
    print(f"coefficient of determination: {r_sq}")
    print(f"intercept: {reg.intercept_}")
    print(f"coefficients: {reg.coef_}")
    if plot:
        plt.figure()
        plt.scatter(x,noisy_y)
        plt.plot(x,y,'r')
        plt.plot(x, reg.predict(x.reshape(-1,1)),'g')
        plt.show()
        
    with open('linreg_dataset_2D.csv', 'w') as file:
        file.write("####################################################\n")
        file.write("# 2D randomly generated linear regression dataset  #\n")
        file.write(f"# generated on: {datetime.now()}         #\n")
        file.write(f"# number of points: {NUMPTS}                           #\n")
        file.write(f"# generated with slope: {slope:.9f}                #\n")
        file.write(f"# generated with intercept: {intercept:.9f}            #\n")
        file.write(f"# generated with normal noise std: {noisestd:.9f}     #\n")
        file.write(f"# fit slope: {reg.coef_[0]:.9f}                           #\n")
        file.write(f"# fit intercept: {reg.intercept_:.9f}                       #\n")
        file.write("####################################################\n")
        file.write("index,x,y\n")
        for i, xi in enumerate(x):
            file.write(f"{i},{xi:.9f},{noisy_y[i]:.9f}\n")
        

def generate_random_linear_3D(x0min, x0max, 
                              x1min, x1max, 
                              slope_x0, slope_x1, intercept,
                              noisestd,
                              plot=False):
    xx0 = np.linspace(x0min, x0max, NUMPTS)
    xx1 = np.linspace(x1min, x0max, NUMPTS)
    x0,x1 = np.meshgrid(xx0,xx1)
    x0 = x0.flatten()
    x1 = x1.flatten()
    X = list(zip(x0,x1))
    y = x0 * slope_x0 + x1 * slope_x1 + intercept    
    noise = np.random.normal(loc=0.0, scale = noisestd, size =y.shape)
    noisy_y = y + noise
    
    reg = LinearRegression().fit(X,noisy_y)
    r_sq = reg.score(X, y)
    print(f"coefficient of determination: {r_sq}")
    print(f"intercept: {reg.intercept_}")
    print(f"coefficients: {reg.coef_}")
        
    if plot:
        fig = plt.figure()
        ax = fig.add_subplot(projection='3d')
        ax.scatter(x0,x1,noisy_y, marker='o')
    with open('linreg_dataset_3D.csv', 'w') as file:
        file.write("####################################################\n")
        file.write("# 3D randomly generated linear regression dataset  #\n")
        file.write("# y = beta_0 * x0 + beta_1 * x1 + intercept        #\n")
        file.write(f"# generated on: {datetime.now()}         #\n")
        file.write(f"# number of points: {NUMPTS}x{NUMPTS}                           #\n")
        file.write(f"# generated with slope_x0: {slope_x0:.9f}          #\n")
        file.write(f"# generated with slope_x1: {slope_x1:.9f}          #\n")
        file.write(f"# generated with intercept: {intercept:.9f}            #\n")
        file.write(f"# generated with normal noise std: {noisestd:.9f}     #\n")
        file.write(f"# fit slope_x0: {reg.coef_[0]:.9f}                        #\n")
        file.write(f"# fit slope_x1: {reg.coef_[1]:.9f}                        #\n")
        file.write(f"# fit intercept: {reg.intercept_:.9f}                       #\n")
        file.write("####################################################\n")
        file.write("index,x0,x1,y\n")
        for i, xi in enumerate(x0):
            file.write(f"{i},{x0[i]:.9f},{x1[i]},{noisy_y[i]:.9f}\n")

def generate_random_linear_5D(xmin_arr,xmax_arr,
                              lincoeff, intercept,
                              noisestd
                              ):
    xx0 = np.linspace(xmin_arr[0], xmax_arr[0], 25)
    xx1 = np.linspace(xmin_arr[1], xmax_arr[1], 25)
    xx2 = np.linspace(xmin_arr[2], xmax_arr[2], 25)
    xx3 = np.linspace(xmin_arr[3], xmax_arr[3], 25)
    
    x0,x1,x2,x3 = np.meshgrid(xx0,xx1,xx2,xx3)
    
    x0 = x0.flatten()
    x1 = x1.flatten()
    x2 = x2.flatten()
    x3 = x3.flatten()
    
    X = list(zip(x0,x1,x2,x3))
    y = x0 * lincoeff[0] + x1 * lincoeff[1] + x2 * lincoeff[2]  + x3 * lincoeff[3] + intercept
    noise = np.random.normal(loc=0.0, scale = noisestd, size =y.shape)
    noisy_y = y + noise
    
    reg = LinearRegression().fit(X,noisy_y)
    r_sq = reg.score(X, y)
    print(f"coefficient of determination: {r_sq}")
    print(f"intercept: {reg.intercept_}")
    print(f"coefficients: {reg.coef_}")
    
    with open('linreg_dataset_5D.csv', 'w') as file:
        file.write("#########################################################################\n")
        file.write("# 3D randomly generated linear regression dataset                       #\n")
        file.write("# y = beta_0 * x0 + beta_1 * x1 + beta_2 * x2 + beta_2 * x3 + intercept #\n")
        file.write(f"# generated on: {datetime.now()}".ljust(72) + "#\n")
        file.write("# number of points: 25x25x25x25".ljust(72)+"#\n")
        file.write(f"# generated with slope_x0: {lincoeff[0]:.9f}".ljust(72)+"#\n")
        file.write(f"# generated with slope_x1: {lincoeff[1]:.9f}".ljust(72)+"#\n")
        file.write(f"# generated with slope_x2: {lincoeff[2]:.9f}".ljust(72)+"#\n")
        file.write(f"# generated with slope_x3: {lincoeff[3]:.9f}".ljust(72)+"#\n")
        file.write(f"# generated with intercept: {intercept:.9f}".ljust(72)+"#\n")
        file.write(f"# generated with normal noise std: {noisestd:.9f}".ljust(72)+"#\n")
        file.write(f"# fit slope_x0: {reg.coef_[0]:.9f}".ljust(72)+"#\n")
        file.write(f"# fit slope_x1: {reg.coef_[1]:.9f}".ljust(72)+"#\n")
        file.write(f"# fit slope_x1: {reg.coef_[2]:.9f}".ljust(72)+"#\n")
        file.write(f"# fit slope_x1: {reg.coef_[3]:.9f}".ljust(72)+"#\n")
        file.write(f"# fit intercept: {reg.intercept_:.9f}".ljust(72)+"#\n")
        file.write("#########################################################################\n")
        
        file.write("index,x0,x1,x2,x3,y\n")
        for i, xi in enumerate(x0):
            file.write(f"{i},{x0[i]:.9f},{x1[i]},{noisy_y[i]:.9f}\n")
    
if __name__=="__main__":
    generate_random_linear_2D(-1, 1, 1.2345, 2.12515, 0.1, plot=True)
    generate_random_linear_3D(-20, 13, 
                              -5,10,
                              3.141592653589793, -3.141592653589793, 2.718281828459045, 0.7124, plot=False)
    generate_random_linear_5D([-1,0,-2,3], [-0.5, 2, 5, 7],
                              [1.0, 1.5, np.sqrt(2), -np.sqrt(3)],
                               2.718281828459045, 0.7124)