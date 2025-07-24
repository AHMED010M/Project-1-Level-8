```markdown
# 🏦 C++ Banking Management System

A simple C++ console-based banking system that manages clients, bank accounts, users, and their permissions.  
Built using `struct`, `enum`, `fstream`, and bitwise operations.

---

## 📁 Project Structure

- `Login.cpp`: Handles user authentication.
- `MainMenue.cpp`: Manages main menu navigation, user permissions, and routing.
- `Clients.cpp`: Displays, adds, deletes, finds, and updates client data.
- `Transactions.cpp`: Deposit and withdraw operations.
- `Users.cpp`: User management (Add, Delete, Update, List).
- `Clients.txt` / `Users.txt`: Text files used for storing data persistently.

---

## 👥 Features

- 🔐 Login system with permissions per user.
- 👤 Manage clients (Add / Update / Delete / Find).
- 💰 Handle transactions (Deposit / Withdraw).
- 🧑‍💼 Manage system users with specific privileges.
- 💾 Read/Write persistent data using `.txt` files.
- 🎛 Console UI with dynamic menus and confirmation messages.

---

## 🧠 Concepts Used

- `Struct`: For client and user data.
- `Vector`: To store collections of clients/users in memory.
- `Bitwise Enum Flags`: To manage user roles and access control.
- `File Handling`: Reading and writing to text files.
- `Console UI`: Colored menus, confirmation screens, and input validation.

---

## 🔑 Permissions System

Each user has access based on the following permissions:

| Permission Flag     | Meaning             |
|---------------------|----------------------|
| `pListClients`      | View client list     |
| `pAddNewClient`     | Add new clients      |
| `pDeleteClient`     | Delete existing clients |
| `pUpdateClients`    | Edit client info     |
| `pFindClient`       | Search clients       |
| `pTranactions`      | Withdraw/Deposit     |
| `pManageUsers`      | Admin access to users |
| `-1`                | Full access (Admin)  |

---

## 🧪 How to Run

1. Compile all `.cpp` files together (using g++ or any IDE like Code::Blocks or Visual Studio).
2. Make sure `Clients.txt` and `Users.txt` exist in the same directory.
3. Run the program and login using a valid user from `Users.txt`.

---

## 📌 Example User Record (Users.txt)

```

ahmed|1234|127
admin|admin|255

```

---

## 🚀 Future Improvements

- Convert to OOP with classes.
- Add GUI using Qt or C++/CLI.
- Password encryption.
- Better input validation and logging system.

---

## 💻 Screenshots

> (You can attach CLI screenshots here later)

---

## 🧑‍💻 Made by Ahmed in 12 hours ⏱  
```

---
