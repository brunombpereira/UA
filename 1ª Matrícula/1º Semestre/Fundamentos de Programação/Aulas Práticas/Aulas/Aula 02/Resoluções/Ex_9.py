import math

ctp = float(input('Qual a nota de CTP? '))
cp = float(input('Qual a nota de CP? '))

if (ctp and cp >= 6.5):
    final_mark = 0.30 * ctp + 0.70 * cp

    if (final_mark < 10):
        atpr = float(input('Qual a nota de ATPR? '))
        apr = float(input('Qual a nota de APR? '))

        final_mark = 0.30 * max(ctp, atpr) + 0.70 * max(cp, apr)
        print(f'Nota final = {final_mark}.')
    else:
        print(f'Nota final = {final_mark}.')
else:
    print('---Error 66---')
