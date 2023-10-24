# Pokémon Fire Red Universal Voicegroup + HQ Mixer
Esta inyección de código inserta el voicegroup universal de FE7 de Blazer + el HQ Mixer 4.0 de Ipatix + Acimut's Drumkit, con la posibilidad de cambiar los archivos MIDI, los samples de instrumentos, modificar los voicegroup; al igual que en decompilaciones. Ofrece una experiencia de sonido inigualable para pokémon de GBA con una frecuencia de muestreo a 21024Hz.

## Sample rate: 21024Hz (no incluye gritos)

***Notas:***

- Debido a la poca IWRAM disponible en Pokémon Fire Red, esta inyección desabilita el sistema de ayuda ocpuando la EWRAM que ésta ocupa, y reasignando la RAM necesaria para funcionar.

### Características:
+ Compatible con Pokémon Fire Red 1.0 BPRE.
+ Frecuencia de muestreo aumentada a 21024Hz.
+ 12 canales
+ 16 tracks
+ Grupo de voces y tabla de canciones reescritos en lenguaje C para facilitar la edición
+ HQ Mixer 4.0 de ipatix.
+ Voicegroup universal (FE7 de Blazer).
+ Increíbles samples de Drumkit por Acimut.
+ Posibilidad de expandir y modificar la tabla de canciones.
+ Posibilidad de insertar en espacio expandido.
+ Trae un reproductor para probar las MIDI y los gritos.
+ Todo por un poco menos de 3MB.

### Requisitos:
- Una ROM de Fire Red 1.0 BPRE
- DevkitARM (con gcc v12.0 o superior) (recomendado r60 o más reciente) [devkitARM r62 x64 (gcc v13.2.0)](https://www.mediafire.com/file/nbyos6a2tlvo7bq/devkitARM_%255Bgcc_v13.2.0%255D_%255Br62%255D.7z/file)
- [ARMIPS v0.11.0](https://github.com/Kingcom/armips/releases/download/v0.11.0/armips-v0.11.0-windows-x86.7z)
- Para compilar es necesario tener preproc.exe, gbagfx.exe, mid2agb.exe y aif2pcm.exe dentro alguna ruta de la variable PATH. [x86](https://www.mediafire.com/file/v1w09jxv9e0f5df/gba-tools_x86.rar/file) [x64](https://www.mediafire.com/file/sdnyh09nbggye1r/gba-tools.rar/file)

### Instrucciones de compilación:

1. En el archivo config.mk, buscar y modificar la siguiente línea por un offset alineado con suficiente espacio libre (0x300000 bytes o más):

      `OFFSET ?= 0x08800000`

2. Luego de pegar una copia de tu rom en la carpeta raíz del proyecto, cambian el nombre de la rom al código de la rom:

       FIRE RED:         BPRE.gba


3.  Compilan ejecutando make con su terminal, y una rom con la inyección aparecerá en una carpeta llamada build.

    Nota: Si compilan desde Windows con CMD o Powershell, es posible compilar usando `make -jN`, donde pueden cambiar `N` por el número de hilos de su CPU reduciendo considerablemente el tiempo de compilación. Recomiendo compilar este proyecto desde Powershell (necesario tener devkitPro correctamente instalado). Por ejemplo, yo compilo desde Powershell usando el comando `time make -j6` para comprobar el tiempo que ocupa la compilación (cerca de 30 segundos con 6 hilos de CPU y almacenamiento SSD). No usar el comando time con CMD en este contexto.

4. En un script usar el special 0xB para visualizar el reproductor de música (pensado para hacer pruebas de sonido, no como una característica jugable).

### Información extra y créditos:

+ El voicegroup universal fue tomado de [este commit](https://github.com/Xhyzi/pokeemerald/commit/b091c0047fa4ef3645f3b29a63f9b0cd0aad51b8), y me tomé la molestia de documentar los samples y los voicegroup hasta cierto punto.

+ El archivo m4a_1.s fue tomado [de aquí ](https://raw.githubusercontent.com/Kurausukun/pokeemerald/newmix/src/m4a_1.s), pero originalmente pertenece a [este repositorio](https://github.com/ipatix/gba-hq-mixer) de Ipatix.

+ La implementación del HQ Mixer 4.0 de Ipatix fue realizada a través de [esta guía](https://github.com/pret/pokeemerald/wiki/Implementing-ipatix's-High-Quality-Audio-Mixer).

- Archivos dentro de la carpeta include fueron tomados de pokefirered.

