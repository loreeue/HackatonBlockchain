# 📚 NALANDA

## 🚀 ¿Qué es NALANDA?
**NALANDA** es una plataforma revolucionaria inspirada en las antiguas bibliotecas que actuaban como centros de formación y conocimiento para médicos, psicólogos, historiadores y administradores. Este proyecto busca ser el archivo definitivo del conocimiento acumulado durante siglos, utilizando **blockchain**, **inteligencia artificial (IA)** y el **sistema IPFS** con la API de **Pinata.cloud**, para garantizar que la información sea accesible, inmutable y siempre actualizada.

---

## 🛠️ Funcionalidades principales

### 1. **Almacén descentralizado de libros**
- Los libros y sus metadatos se almacenan en **IPFS** a través de la API de **Pinata.cloud**, asegurando un almacenamiento eficiente, escalable y permanente.
- Cada libro es referenciado en la blockchain mediante un hash único generado en IPFS.
- Se implementará un sistema de validación distribuida para garantizar la autenticidad de los libros antes de su incorporación.

### 2. **Actualización dinámica de la biblioteca**
- La blockchain actúa como un índice para los archivos almacenados en IPFS, lo que permite actualizaciones constantes y evita duplicación o corrupción de datos.
- Cada nodo de la red mantiene una referencia válida a los archivos, eliminando puntos únicos de falla.

### 3. **IA para enseñanza personalizada**
- La IA integrada utiliza los datos almacenados en IPFS para:
  - **Explicar conocimientos complejos** en formatos modernos (podcasts, chats interactivos, resúmenes).
  - **Optimizar la enseñanza** adaptándose al estilo de aprendizaje del usuario.
  - Proporcionar **asesoría especializada** en áreas específicas con información siempre actualizada.

### 4. **Conocimiento accesible y permanente**
- El uso de IPFS con **Pinata.cloud** garantiza:
  - **Accesibilidad global:** Los libros son accesibles desde cualquier lugar con conexión a Internet.
  - **Reducción de costos:** Al aprovechar un sistema descentralizado, el costo de almacenamiento se minimiza en comparación con soluciones centralizadas.
  - **Resiliencia:** Los datos permanecen seguros incluso en caso de ataques o caídas de nodos.

---

## 🌐 Visión del proyecto

**NALANDA** no solo es un repositorio de libros. Es un ecosistema donde:
- **Las personas se forman y se convierten en expertos** en diversas áreas.
- **El conocimiento se almacena permanentemente**, siendo accesible para generaciones futuras.
- La IA mejora continuamente sus capacidades al recibir información verídica y actualizada.
- Se utiliza la **blockchain y IPFS** para garantizar la transparencia y la seguridad de la información.

---

## 📋 Cómo desplegar la web

1. Clonar el repositorio:
   ```bash
   git clone <URL_DEL_REPOSITORIO>
   cd <NOMBRE_DEL_REPOSITORIO>
   ```
2. Actualizar submódulos del repositorio:
   ```bash
   git submodule update --init --recursive
   ```
3. Instalar `cargo-stylus`:
   ```bash
   cargo install cargo-stylus
   ```
4. Agregar el objetivo para compilar en WebAssembly:
   ```bash
   rustup target add wasm32-unknown-unknown
   ```
5. Crear el archivo `.env` en el directorio raíz con el siguiente contenido:
   ```
   PRIVATE_KEY=0x<TU_CLAVE_PRIVADA>
   ```
6. Cambiar la clave privada en el paso 5 del `Makefile`.
7. Compilar y desplegar:
   ```bash
   make re
   cargo stylus check --wasm-file ./contract.wasm -e https://sepolia-rollup.arbitrum.io/rpc
   cargo stylus deploy --wasm-file ./contract.wasm -e https://sepolia-rollup.arbitrum.io/rpc --cargo-stylus-version 0.5.3 --private-key 0x<TU_CLAVE_PRIVADA>
   ```
8. Actualizar las direcciones del contrato en `index.ts` y `page.tsx`.
9. Instalar las dependencias del frontend:
   ```bash
   npm install wagmi @wagmi/core ethers
   npm install
   ```
10. Ejecutar el frontend:
    ```bash
    make frontend
    ```
11. Abrir la web en el navegador: [http://localhost:3000/devBook](http://localhost:3000/devBook).

---

## 💻 Tecnologías utilizadas

### Almacenamiento
- **IPFS con Pinata.cloud:** Para almacenamiento descentralizado, escalable y eficiente.

### Blockchain
- **Ethereum / Arbitrum:** Para la gestión de contratos inteligentes y la validación de información.

### Inteligencia Artificial
- **Modelos de lenguaje avanzado (GPT, BERT):** Para interacción y enseñanza.
- **NLP y técnicas de aprendizaje profundo:** Para análisis y síntesis de conocimiento.

### Frontend
- **React y Next.js:** Para una interfaz moderna y fácil de usar.
- **Tailwind CSS:** Para un diseño visual atractivo.

### Backend
- **Node.js:** Para el manejo de lógica del servidor y APIs.
- **Express:** Para gestionar solicitudes entre el frontend y la blockchain.

---

## 📞 Contacto
Si tienes dudas, sugerencias o quieres contribuir, no dudes en contactarnos:
- **GitHub Loreto:** [github.com/loreeue](https://github.com/loreeue)
- **GitHub Cristian:** [github.com/CristianYepes](https://github.com/CristianYepes)

---
