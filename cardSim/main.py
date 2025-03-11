import random
import tkinter as tk
from PIL import Image, ImageTk

suits = ["spades", "hearts", "diamonds", "clubs"]
numbers = ["ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"]
plus = ["2", "3", "4", "5", "6"]
zero = ["7", "8", "9"]
minus = ["ace", "10", "jack", "queen", "king"]

cards = []
for suit in suits:
    for number in numbers:
        combination = (number, suit)
        cards.append(combination)

# Create the main window
root = tk.Tk()
root.title("Display an Image")

count = 0

# Load and display the image
number, suit = random.choice(cards)

if number in plus:
    count += 1
elif number in minus:
    count -= 1
print (count)

cardPath = f"./images/{number}_of_{suit}.png"
image = Image.open(cardPath)
image_tk = ImageTk.PhotoImage(image)
label = tk.Label(root, image=image_tk)
label.pack()

# Function to exit the application
def exit_app():
    root.destroy()  # Closes the window

def next_card():
    global count
    global current_count
    current_count.destroy()

    number, suit = random.choice(cards)

    if number in plus:
        count += 1
    elif number in minus:
        count -= 1

    print(count)

    cardPath = f"./images/{number}_of_{suit}.png"
    image = Image.open(cardPath)
    image_tk = ImageTk.PhotoImage(image)
    label.config(image=image_tk)
    label.image = image_tk

def show_count():
    global current_count
    global count

    current_count = tk.Text(root, height=10, width=40)
    current_count.pack(padx=20, pady=60)
    current_count.insert(tk.END, f"the count is: {count}")

# Create the exit button and bind it to the exit_app function
exit_button = tk.Button(root, text="Exit", command=exit_app)
exit_button.pack(pady=10)

# Create the exit button and bind it to the exit_app function
show_count = tk.Button(root, text="Show Count", command=show_count)
show_count.pack(pady=20)

# Create the exit button and bind it to the exit_app function
next_button = tk.Button(root, text="Next", command=next_card)
next_button.pack(pady=30)


current_count = tk.Text(root, height=10, width=40)
current_count.pack(padx=20, pady=60)
current_count.insert(tk.END, f"the count is: {0}")

# Run the Tkinter event loop
root.mainloop()

# Run the Tkinter event loop
root.mainloop()
