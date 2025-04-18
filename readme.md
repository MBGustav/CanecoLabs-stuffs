# Repositorio das implementações do Caneco


# 1. Porta
- vai ter conexao (wifi/bluetooth) para comm. com outro mcu/servidor.
- Leitura de carterinha via rfid/nfc.
- Cadastramento via porta(entrada ou saida?)
- Senha mestra, caso desejemos acessar o caneco. 
- Acesso via chave mecanica. 


| Descrição | BIT-0 | BIT-1 | BIT-2 | BIT-3 | BIT-4 | BIT-5 | BIT-6 | BIT-7 |
|-----------|-------|-------|-------|-------|-------|-------|-------|-------|
| 1         | 1     | 0     | 0     | 0     | 1     | 0     | 0     | 0     |
| 2         | 1     | 0     | 0     | 0     | 0     | 1     | 0     | 0     |
| 3         | 1     | 0     | 0     | 0     | 0     | 0     | 1     | 0     |
| 4         | 0     | 1     | 0     | 0     | 1     | 0     | 0     | 0     |
| 5         | 0     | 1     | 0     | 0     | 0     | 1     | 0     | 0     |
| 6         | 0     | 1     | 0     | 0     | 0     | 0     | 1     | 0     |
| 7         | 0     | 0     | 1     | 0     | 1     | 0     | 0     | 0     |
| 8         | 0     | 0     | 1     | 0     | 0     | 1     | 0     | 0     |
| 9         | 0     | 0     | 1     | 0     | 0     | 0     | 1     | 0     |
| CAD_OFF   | 0     | 0     | 0     | 1     | 1     | 0     | 0     | 0     |
| 0         | 0     | 0     | 0     | 1     | 0     | 1     | 0     | 0     |
| CAD_ON    | 0     | 0     | 0     | 1     | 0     | 0     | 1     | 0     |

- Para que o input do botão seja reconhecido é necessário que no momento em que o bit da linha(BIT-0,BIT-1,BIT-2,BIT-3) receba um pulso HIGH do microcontrolador da porta o arduino mande um HIGH na coluna(BIT-4,BIT-5,BIT-6).

|-------| BIT-4 | BIT-5 | BIT-6 |
|-------|-------|-------|-------|
| BIT-0 |   1   |   2   |   3   |
| BIT-1 |   4   |   5   |   6   |
| BIT-2 |   7   |   8   |   9   |
| BIT-3 |CAD_OFF|   0   |CAD_ON |


- O pulso que as linhas recebem são sempre em ordem, sendo o primeiro no BIT-0 e segue a ordem até o BIT-3 sendo o intevalo entre cada edge de subida(entre cada bit) aproximadamente 0.5 microsegundos.

- Nesse projeto estamos usando o Arduino NANO, que só possui 2 pinos de reação, que seriam capazes de ler esse pulso vindo da linha. Por conta de termos 4 linhas e apenas 2 pinos de reação leremos apenas o pulso do BIT-0 e para os outros bits da linha vamos calcular o pulso deles.

- 