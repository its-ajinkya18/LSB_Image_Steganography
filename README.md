# 🧠 LSB Image Steganography in C

---

## 📘 Project Overview

This project implements **LSB (Least Significant Bit) Image Steganography** using the **C programming language**.

Steganography is the technique of **hiding secret information inside another file** such that the presence of the data remains hidden.
In this implementation, a **text file is embedded inside a BMP image** without causing visible changes to the image.

The project highlights key **systems programming concepts** including:

* Bitwise Operations
* File Handling
* Memory Manipulation
* Data Encoding & Decoding
* Modular C Programming

---

## ✨ Features

🔐 Encode secret text data inside a **BMP image**
🔓 Decode and recover hidden data from the image
🧠 Uses **LSB bit manipulation technique**
🧩 Supports **24-bit BMP images**
⚙️ Validates file formats and image capacity
📂 Modular code design with header files
📜 Logging messages during encoding & decoding

---

## 🧪 Demo

### Encode Secret File

```bash
./a.out -e input.bmp secret.txt stego.bmp
```

### Decode Hidden File

```bash
./a.out -d stego.bmp output.txt
```

---

## 🖼 Example Workflow

1️⃣ Input Image

```
input.bmp
```

2️⃣ Secret File

```
secret.txt
```

3️⃣ Output Stego Image

```
stego.bmp
```

The **stego image visually looks identical to the original image**, but secretly contains embedded data.

---

## ⚙️ How to Compile and Run

### 1️⃣ Clone Repository

```bash
git clone https://github.com/yourusername/LSB-Steganography-C-Implementation.git
```

### 2️⃣ Navigate to Project Directory

```bash
cd LSB-Steganography-C-Implementation
```

### 3️⃣ Build Project

```bash
make
```

### 4️⃣ Encode Mode

```bash
./a.out -e <source_image.bmp> <secret.txt> <stego_image.bmp>
```

Example:

```bash
./a.out -e sample/input.bmp sample/secret.txt sample/stego.bmp
```

### 5️⃣ Decode Mode

```bash
./a.out -d <stego_image.bmp> <output.txt>
```

Example:

```bash
./a.out -d sample/stego.bmp sample/output.txt
```

---

## 📁 Project Structure

```
LSB-Steganography-C-Implementation
│
├── main.c          # Entry point of the application
├── encode.c        # Encoding logic
├── decode.c        # Decoding logic
├── encode.h        # Encoding function declarations
├── decode.h        # Decoding function declarations
├── types.h         # Custom data types
├── Makefile        # Build automation
├── README.md       # Project documentation
│
└── sample
    ├── input.bmp
    ├── secret.txt
    └── stego.bmp
```

---

## 🧮 Concept Behind LSB Steganography

LSB steganography works by **modifying the least significant bits of image pixels** to store secret information.

Example:

```
Original Pixel   : 10010110
Embedded Pixel   : 10010111
```

Only the **last bit changes**, so the visual difference is **imperceptible to the human eye**.

This method allows secure **data hiding while maintaining image quality**.

---

## 📚 Learning Outcomes

Through this project I gained practical experience with:

* Bitwise data manipulation
* Binary file handling in C
* Image file structure (BMP)
* Data encoding and decoding techniques
* Writing modular and maintainable C programs

---

## 🔮 Future Improvements

* 🖼 Support **PNG and JPEG images**
* 🖥 Create **GUI interface**
* 🎧 Implement **audio steganography**

---

## 👨‍💻 Author

**Ajinkya Subhash Kadam**\
Electronics and Computer Engineer\
Embedded Systems Enthusiast

🔗 LinkedIn
https://www.linkedin.com/in/ajinkya-kadam-54a51b283

---

## ⭐ Support

If you found this project useful:

⭐ Star this repository on GitHub
📢 Share it with others interested in **C programming and steganography**
