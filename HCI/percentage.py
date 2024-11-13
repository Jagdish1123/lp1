import tkinter as tk
from tkinter import messagebox

class MarksWindow:
    def __init__(self, root): 
        self.root = root
        self.root.geometry("400x300")
        self.root.title("Marksheet")

        self.subjects = ["Maths", "Science", "Physics"]
        self.marks_list = []

        for subject in self.subjects:
            label = tk.Label(root, text=f"Enter Marks of {subject}")
            label.pack(pady=5)  # Adjusted padding for better spacing
            entry = tk.Entry(root)
            entry.pack(pady=5)
            self.marks_list.append(entry)
        
        self.click_button = tk.Button(root, text="Calculate Percentage", command=self.cal_percent)
        self.click_button.pack(pady=10)

    def cal_percent(self):
        total_marks = 0
        max_marks = 100 * len(self.marks_list)
        try:
            for entry in self.marks_list:
                marks = int(entry.get())
                total_marks += marks
            percentage = (total_marks / max_marks) * 100
            messagebox.showinfo("Percentage", f"Your percentage is {percentage:.2f}%")
        except ValueError:
            messagebox.showerror("Input Error", "Please enter valid integer marks.")



if __name__ == "__main__":  # Corrected from "main_" to "__main__"
    root = tk.Tk()
    window = MarksWindow(root)
    root.mainloop()
