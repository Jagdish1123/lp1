import tkinter as tk 
from tkinter import messagebox

class Railway:
    def __init__(self, root):
        self.root = root
        self.root.title("Railway Reservation System")
        self.root.geometry("400x400")

        # Train Number
        self.train_label = tk.Label(root, text="Enter Train Number")
        self.train_label.pack(pady=5)
        self.train_entry = tk.Entry(root)
        self.train_entry.pack(pady=5)

        # Source
        self.source_label = tk.Label(root, text="Enter Source")
        self.source_label.pack(pady=5)
        self.source_entry = tk.Entry(root)
        self.source_entry.pack(pady=5)

        # Destination
        self.dest_label = tk.Label(root, text="Enter Destination")
        self.dest_label.pack(pady=5)
        self.dest_entry = tk.Entry(root)
        self.dest_entry.pack(pady=5)

        # Passenger Name
        self.name_label = tk.Label(root, text="Enter Passenger Name")
        self.name_label.pack(pady=5)
        self.name_entry = tk.Entry(root)
        self.name_entry.pack(pady=5)

        # Class Selection
        self.seat_label = tk.Label(root, text="Select Class")
        self.seat_label.pack(pady=5)

        self.var = tk.StringVar(value="Sleeper")
        self.sleeper = tk.Radiobutton(root, text="Sleeper", value="Sleeper", variable=self.var)
        self.sleeper.pack(pady=2)
        self.firstclass = tk.Radiobutton(root, text="First Class", value="First Class", variable=self.var)
        self.firstclass.pack(pady=2)
        self.secondclass = tk.Radiobutton(root, text="Second Class", value="Second Class", variable=self.var)
        self.secondclass.pack(pady=2)

        # Reserve Button
        self.submit_button = tk.Button(root, text="Reserve Ticket", command=self.reserve_ticket)
        self.submit_button.pack(pady=10)

    def reserve_ticket(self):
        train = self.train_entry.get()
        source = self.source_entry.get()
        destination = self.dest_entry.get()
        passenger_name = self.name_entry.get()
        class_type = self.var.get()

        if train and source and destination and passenger_name:
            messagebox.showinfo("Success", f"Ticket reserved for {passenger_name} \nTrain: {train} \nFrom: {source} \nTo: {destination} \nClass: {class_type}")
        else:
            messagebox.showwarning("Input Error", "Please fill in all fields")

# Main program execution
if __name__ == "__main__":
    root = tk.Tk()
    app = Railway(root)
    root.mainloop()