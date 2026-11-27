# Sistema de Gerenciamento de Senhas de Atendimento Clínico

## 1. Objetivo e funcionalidades

Aplicação acadêmica em C para cadastrar pacientes, classificar prioridades e organizar filas de atendimento.

O sistema oferece:
- Cadastro e validação dos dados dos pacientes.
- Classificação automática e geração de senhas sequenciais independentes (`N001`, `P001`, `U001`).
- Filas FIFO (primeiro a entrar, primeiro a sair), na ordem **Urgente > Preferencial > Normal**.
- Consulta e chamada da próxima senha, identificação do paciente em atendimento e finalização.
- Painel com paciente em atendimento, próximas senhas e quantidade de pessoas aguardando por categoria.

### Regras de classificação

- **N — Normal:** sem condição de prioridade.
- **P — Preferencial:** gestante, lactante, pessoa com necessidade especial ou obesidade, mulher com 60 anos ou mais ou homem com 65 anos ou mais.
- **U — Urgente:** idade acima de 80 anos.

A categoria urgente tem prioridade sobre a preferencial, e esta sobre a normal. Dentro de cada fila, vale a ordem de chegada.

> **Importante:** são regras didáticas da atividade. Não substituem avaliação clínica nem representam integralmente a legislação.

## 2. Organização dos arquivos

Mantenha todos os arquivos na mesma pasta:

| Arquivo | Função |
|---|---|
| `main.c` | Menu e coordenação do sistema. |
| `paciente.h` / `paciente.c` | Estrutura, cadastro, validação e classificação. |
| `fila.h` / `fila.c` | Estrutura e operações das filas FIFO. |
| `sistema.h` / `sistema.c` | Integração das filas, senhas, atendimentos e painel. |

**Diferença entre `.h` e `.c`:** arquivos `.h` declaram estruturas e protótipos; arquivos `.c` implementam as funções. O `main.c` coordena os módulos.

## 3. Requisitos para executar no Windows

- **Visual Studio Code:** editor para abrir e editar o projeto.
- **GCC:** compilador necessário para transformar os arquivos C em executável.
- **Extensão C/C++ da Microsoft:** recomendada para recursos de edição; ela não instala o GCC.

Downloads oficiais:
- [Visual Studio Code](https://code.visualstudio.com/)
- [Extensão C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [MSYS2](https://www.msys2.org/)

## 4. Instalar e configurar o GCC

Este projeto usa MSYS2 com MinGW-w64 UCRT64.

1. Instale o MSYS2 pelo site oficial. Se possível, mantenha a pasta padrão `C:\msys64`.
2. Abra **MSYS2 UCRT64** pelo menu Iniciar.
3. Execute:

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

4. Pressione `Enter` para aceitar a seleção padrão, se solicitado. Quando perguntar `Proceed with installation?`, digite `Y` e pressione `Enter`.
5. No Windows, pesquise **Editar as variáveis de ambiente para sua conta**. Em `Path`, clique em **Editar > Novo** e adicione:

```text
C:\msys64\ucrt64\bin
```

6. Confirme as janelas, feche e abra novamente o VS Code.

> Se instalou o MSYS2 em outro local, ajuste o caminho para a pasta `ucrt64\bin` correspondente.

Para testar, abra **Terminal > Novo Terminal** no VS Code e digite:

```powershell
gcc --version
```

Se aparecer a versão, o GCC está disponível. Se `gcc` não for reconhecido, confira o PATH e reinicie o VS Code.

## 5. Abrir, compilar e executar no VS Code

1. Descompacte o projeto, se necessário.
2. No VS Code, clique em **Arquivo > Abrir Pasta** e selecione a pasta que contém os sete arquivos `.c` e `.h`.
3. Abra **Terminal > Novo Terminal** (atalho: `Ctrl + Shift + \``).
4. Confira se o terminal está na pasta do projeto:

```powershell
dir
```

A listagem deve mostrar `main.c`, `paciente.c`, `paciente.h`, `fila.c`, `fila.h`, `sistema.c` e `sistema.h`. Se não aparecerem, abra a pasta correta no VS Code.

5. Compile todos os arquivos `.c` juntos:

```powershell
gcc -std=c11 -Wall -Wextra -pedantic main.c paciente.c fila.c sistema.c -o clinica
```

6. Se a compilação terminar sem erros, execute:

```powershell
.\clinica.exe
```

**Atenção:** compile e execute em comandos separados. Os quatro arquivos `.c` precisam estar no comando porque contêm as implementações. Os `.h` são incluídos pelos arquivos `.c` e não precisam ser listados.

## 6. Por que a execução é diferente no OnlineGDB?

O projeto foi modularizado em vários arquivos. Por isso, não basta compilar somente `main.c`: também são necessárias as implementações de `paciente.c`, `fila.c` e `sistema.c`.

No VS Code, o comando GCC informa explicitamente os quatro arquivos `.c`. No OnlineGDB, é necessário adicionar todos ao mesmo projeto e configurar a compilação conjunta. Se apenas `main.c` for compilado, podem ocorrer erros como `undefined reference` (referência indefinida).

O OnlineGDB não é incompatível com C; a execução depende de a configuração permitir vários arquivos-fonte. Se estiver limitado a um único arquivo, não executará este projeto modularizado da mesma forma.

## 7. Problemas comuns

| Erro ou situação | Causa e solução |
|---|---|
| `gcc não é reconhecido` | GCC ausente ou PATH incorreto. Confira `C:\msys64\ucrt64\bin`, reabra o VS Code e teste `gcc --version`. |
| Arquivo não encontrado | Terminal na pasta errada. Use `dir` e abra a pasta que contém os arquivos do projeto. |
| `undefined reference` | Um arquivo `.c` ficou fora da compilação. Use o comando completo da seção 5. |
| `clinica.exe` não encontrado | A compilação não terminou corretamente. Verifique os erros e se o executável foi criado. |
| Terminal aguardando | O programa pode estar esperando uma resposta. Leia a mensagem, digite a opção e pressione `Enter`. `Ctrl + C` interrompe a execução. |

## 8. Exemplo de utilização

Um paciente com 85 anos recebe uma senha urgente, como `U001`. Um paciente sem prioridade recebe uma senha normal, como `N001`. A senha urgente será chamada primeiro, mesmo que tenha sido gerada depois.

## 9. Conceitos aplicados

Linguagem C, funções, modularização (`.h` e `.c`), `struct`, vetores, ponteiros, passagem de parâmetros, retorno de funções, condicionais, laços de repetição e filas FIFO.

## 10. Observação final

Projeto desenvolvido para fins acadêmicos. A classificação segue exclusivamente as regras didáticas do enunciado e não deve ser usada para decisões reais de atendimento clínico.
