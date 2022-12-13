"""
//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//
// CSV struct
//                  [insert_concurrente] [insert_secuencial] [find_concurrente] [find_secuencial] [remove_concurrente] [remove_secuencial] [elementos=value] [threads=value]
//  values: test1
//  values: test2
//  values: test3
//  values: ...
//  values: ..
//  values: .
//
// 4 Graficas generadas.
//
"""
import csv
import pip


def install(package):
    pip.main(['install', package])


try:
    import matplotlib
    import pandas
except:
    install('matplotlib')
    install('pandas')

import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('times.csv')
df_insert = pd.DataFrame({
    'Insert Concurrente': df['insert_concurrente'],
    'Insert Secuencial': df['insert_secuencial']
})
df_find = pd.DataFrame({
    'Find Concurrente': df['find_concurrente'],
    'Find Secuencial': df['find_secuencial']
})
df_rem = pd.DataFrame({
    'Rem Concurrente': df['remove_concurrente'],
    'Rem Secuencial': df['remove_secuencial']
})
df_merge = pd.DataFrame({
    'Insert Concurrente': df['insert_concurrente'],
    'Insert Secuencial': df['insert_secuencial'],
    'Find Concurrente': df['find_concurrente'],
    'Find Secuencial': df['find_secuencial'],
    'Rem Concurrente': df['remove_concurrente'],
    'Rem Secuencial': df['remove_secuencial']
})

cvKeys = list(df.keys())

df_insert.plot.line(style={'Insert Concurrente': '#FF0000', 'Insert Secuencial': '#FF8C8C'})
plt.title(f'Tiempo de insertado con {cvKeys[7]} threads y {cvKeys[6]} elementos.', fontsize=14)
plt.savefig("Insert.png")
plt.close()

df_find.plot.line(style={'Find Concurrente': '#002AFF', 'Find Secuencial': '#434683'})
plt.title(f'Tiempo de busqueda con {cvKeys[7]} threads y {cvKeys[6]} elementos.', fontsize=14)
plt.savefig("Find.png")
plt.close()

df_rem.plot.line(style={'Rem Concurrente': '#00FF3E', 'Rem Secuencial': '#1E8604'})
plt.title(f'Tiempo de borrado con {cvKeys[7]} threads y {cvKeys[6]} elementos.', fontsize=14)
plt.savefig("Rem.png")
plt.close()

df_merge.plot.line(style={
    'Insert Concurrente': '#FF0000',
    'Insert Secuencial': '#FF8C8C',
    'Find Concurrente': '#002AFF',
    'Find Secuencial': '#434683',
    'Rem Concurrente': '#00FF3E',
    'Rem Secuencial': '#1E8604',
}, marker='.')
plt.title(f'Tiempo totales de cada operación con {cvKeys[7]} threads y {cvKeys[6]} elementos.', fontsize=14)
plt.savefig("merge.png")
plt.close()
