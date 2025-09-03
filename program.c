import os

TODO_FILE = "todo.txt"

# Load tasks from file
def load_tasks():
    if not os.path.exists(TODO_FILE):
        return []
    with open(TODO_FILE, "r") as file:
        tasks = [line.strip().split(";", 1) for line in file.readlines()]
        return [{"task": t[1], "done": t[0] == "1"} for t in tasks]

# Save tasks to file
def save_tasks(tasks):
    with open(TODO_FILE, "w") as file:
        for task in tasks:
            line = f"{1 if task['done'] else 0};{task['task']}\n"
            file.write(line)

# Display task list
def show_tasks(tasks):
    if not tasks:
        print("No tasks in your list.")
        return
    print("\nYour To-Do List:")
    for idx, task in enumerate(tasks, 1):
        status = "[x]" if task["done"] else "[ ]"
        print(f"{idx}. {status} {task['task']}")
    print()

# Add a task
def add_task(tasks):
    task_text = input("Enter new task: ").strip()
    if task_text:
        tasks.append({"task": task_text, "done": False})
        print("Task added.")
    else:
        print("Task cannot be empty.")

# Mark task as completed
def complete_task(tasks):
    show_tasks(tasks)
    try:
        index = int(input("Enter task number to mark complete: "))
        if 1 <= index <= len(tasks):
            tasks[index - 1]["done"] = True
            print("Task marked as completed.")
        else:
            print("Invalid task number.")
    except ValueError:
        print("Please enter a valid number.")

# Delete a task
def delete_task(tasks):
    show_tasks(tasks)
    try:
        index = int(input("Enter task number to delete: "))
        if 1 <= index <= len(tasks):
            removed = tasks.pop(index - 1)
            print(f"Deleted task: {removed['task']}")
        else:
            print("Invalid task number.")
    except ValueError:
        print("Please enter a valid number.")

# Main menu loop
def main():
    tasks = load_tasks()
    while True:
        print("\n--- To-Do List Menu ---")
        print("1. View tasks")
        print("2. Add task")
        print("3. Complete task")
        print("4. Delete task")
        print("5. Exit")
        choice = input("Choose an option (1-5): ").strip()

        if choice == "1":
            show_tasks(tasks)
        elif choice == "2":
            add_task(tasks)
        elif choice == "3":
            complete_task(tasks)
        elif choice == "4":
            delete_task(tasks)
        elif choice == "5":
            save_tasks(tasks)
            print("Tasks saved. Goodbye!")
            break
        else:
            print("Invalid choice. Please enter 1-5.")

if __name__ == "__main__":
    main()
