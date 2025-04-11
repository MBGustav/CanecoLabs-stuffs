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

