class Todo {
    constructor() {
        // Wczytaj z localStorage lub użyj domyślnych
        const saved = localStorage.getItem("todoTasks");
        this.tasks = saved ? JSON.parse(saved) : [
            { text: "Buy cat's food", date: "2025-11-15", done: false },
            { text: "Go shopping", date: "", done: false }
        ];

        this.container = document.querySelector(".tasksContainer");
        this.taskInput = document.querySelector(".getTaskInput");
        this.dateInput = document.querySelector(".getDateInput");
        this.saveBtn = document.querySelector(".saveBtn");
        this.searchInput = document.querySelector(".searchInput");

        this.saveBtn.addEventListener("click", () => this.addTask());
        this.searchInput.addEventListener("input", () => this.filterTasks());

        this.draw();
    }

    saveToStorage() {
        localStorage.setItem("todoTasks", JSON.stringify(this.tasks));
    }

    draw() {
        this.container.innerHTML = "";
        this.tasks.forEach((task, index) => {
            const li = document.createElement("li");
            li.classList.add("task");
            li.innerHTML = `
                <input type="checkbox" class="taskCheck" ${task.done ? "checked" : ""}/>
                <span class="taskText">${task.text}</span>
                <span class="taskDate">${task.date}</span>
                <button class="deleteBtn" title="Delete task"><i class="fa-solid fa-trash"></i></button>
            `;

            li.querySelector(".deleteBtn").addEventListener("click", (e) => {
                e.stopPropagation();
                this.deleteTask(index);
            });

            li.querySelector(".taskCheck").addEventListener("change", (e) => {
                this.tasks[index].done = e.target.checked;
                this.saveToStorage();
            });

            li.addEventListener("click", (e) => {
                if (e.target.classList.contains("taskCheck") || e.target.closest(".deleteBtn")) return;
                this.editTask(li, index);
            });

            this.container.appendChild(li);
        });
    }

    addTask() {

        const text = this.taskInput.value.trim();
        const date = this.dateInput.value;
        const today = new Date().toISOString().split('T')[0];

        if (!text) return;
        if (text.length < 3 || text.length > 255) {
            alert("Zadanie musi mieć od 3 do 255 znaków");
            return;
        }
        if (date && date < today) {
            alert("Data musi być dziś lub w przyszłości");
            return;
        }

        this.tasks.push({ text, date, done: false });
        this.taskInput.value = "";
        this.dateInput.value = "";
        this.saveToStorage();
        this.filterTasks();
    }

    deleteTask(index) {
        this.tasks.splice(index, 1);
        this.saveToStorage();
        this.filterTasks();
    }

    filterTasks() {
        const query = this.searchInput.value.trim().toLowerCase();
        let filtered = this.tasks;

        if (query.length >= 2) {
            filtered = this.tasks.filter(task =>
                task.text.toLowerCase().includes(query)
            );
        }

        this.container.innerHTML = "";
        filtered.forEach((task, index) => {
            const originalIndex = this.tasks.indexOf(task);
            const li = document.createElement("li");
            li.classList.add("task");

            let displayText = task.text;
            if (query.length >= 2) {
                const regex = new RegExp(`(${query})`, "gi");
                displayText = task.text.replace(regex, "<mark>$1</mark>");
            }

            li.innerHTML = `
                <input type="checkbox" class="taskCheck" ${task.done ? "checked" : ""}/>
                <span class="taskText">${displayText}</span>
                <span class="taskDate">${task.date}</span>
                <button class="deleteBtn" title="Delete task"><i class="fa-solid fa-trash"></i></button>
            `;

            li.querySelector(".deleteBtn").addEventListener("click", (e) => {
                e.stopPropagation();
                this.deleteTask(originalIndex);
            });

            li.querySelector(".taskCheck").addEventListener("change", (e) => {
                this.tasks[originalIndex].done = e.target.checked;
                this.saveToStorage();
                this.filterTasks();
            });

            li.addEventListener("click", (e) => {
                if (e.target.classList.contains("taskCheck") || e.target.closest(".deleteBtn")) return;
                this.editTask(li, originalIndex);
            });

            this.container.appendChild(li);
        });
    }

    editTask(li, index) {
        const task = this.tasks[index];
        const textSpan = li.querySelector(".taskText");
        const dateSpan = li.querySelector(".taskDate");
        const deleteBtn = li.querySelector(".deleteBtn");

        const originalText = task.text;
        const originalDate = task.date;

        const textInput = document.createElement("input");
        textInput.type = "text";
        textInput.value = task.text;
        textInput.classList.add("editText");

        const dateInput = document.createElement("input");
        dateInput.type = "date";
        dateInput.value = task.date;
        dateInput.classList.add("editDate");

        const saveBtn = document.createElement("button");
        saveBtn.classList.add("saveEditBtn");
        saveBtn.innerHTML = '<i class="fa-solid fa-check"> SAVE</i>';
        saveBtn.title = "Zapisz zmiany";

        li.replaceChild(textInput, textSpan);
        li.replaceChild(dateInput, dateSpan);
        li.replaceChild(saveBtn, deleteBtn);

        textInput.focus();
        textInput.select();

        const saveChanges = () => {
            const newText = textInput.value.trim();
            const newDate = dateInput.value;
            const today = new Date().toISOString().split('T')[0];

            if (newText.length < 3 || newText.length > 255) {
                alert("Zadanie musi mieć od 3 do 255 znaków");
                return;
            }
            if (newDate && newDate < today) {
                alert("Data musi być dziś lub w przyszłości");
                return;
            }

            task.text = newText;
            task.date = newDate;
            this.saveToStorage();
            cleanup();
            this.filterTasks();
        };

        const cancelEdit = () => {
            task.text = originalText;
            task.date = originalDate;
            cleanup();
            this.filterTasks();
        };

        const cleanup = () => {
            document.removeEventListener("click", handleClickOutside);
            saveBtn.removeEventListener("click", handleSave);
            textInput.removeEventListener("keydown", handleKeydown);
        };

        const handleSave = (e) => {
            e.stopPropagation();
            saveChanges();
        };

        const handleKeydown = (e) => {
            if (e.key === "Enter") {
                e.preventDefault();
                saveChanges();
            } else if (e.key === "Escape") {
                cancelEdit();
            }
        };

        const handleClickOutside = (e) => {
            if (!li.contains(e.target)) {
                saveChanges();
            }
        };

        saveBtn.addEventListener("click", handleSave);
        textInput.addEventListener("keydown", handleKeydown);
        setTimeout(() => document.addEventListener("click", handleClickOutside), 0);
    }
}

document.addEventListener("DOMContentLoaded", () => new Todo());