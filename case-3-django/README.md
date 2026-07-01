# Case 3: Django Greeting App

## Setup

```powershell
py -3 -m venv .venv
.\.venv\Scripts\activate
py -3 -m pip install -r requirements.txt
py -3 manage.py makemigrations
py -3 manage.py migrate
py -3 manage.py runserver
```

## How To Open The Web App

1. Open PowerShell in the folder `case-3-django`.
2. Activate the virtual environment:

```powershell
.\.venv\Scripts\activate
```

3. Start the Django development server:

```powershell
py -3 manage.py runserver
```

4. Wait until Django shows a message similar to:

```text
Starting development server at http://127.0.0.1:8000/
```

5. Open your browser and go to:

```text
http://127.0.0.1:8000/
```

6. To stop the server later, return to the terminal and press `Ctrl + C`.

## Manual Testing

You can manually test the application with the following scenarios:

1. Open `http://127.0.0.1:8000/` and check that the main page loads correctly.
2. Enter a valid name, for example `Ivan`, and click `Submit`.
3. Confirm that a personalized greeting appears on the page.
4. Confirm that the entered name is added to the list of recent visitors.
5. Submit the form with an empty field and check that an error message appears.
6. Enter another valid name and verify that the new name is also stored and displayed.
7. Refresh the page and make sure previously saved names are still shown, which confirms that data was saved in SQLite.
8. Optionally open the admin panel at `http://127.0.0.1:8000/admin/` after creating a superuser to inspect saved records manually.

## Optional Admin Access

If you want to view saved names through Django admin:

```powershell
py -3 manage.py createsuperuser
```

Then start the server again, open `http://127.0.0.1:8000/admin/`, sign in, and open the `Visitors` section.

## Features

- form for entering a user name;
- validation against empty input;
- saving names into SQLite via a Django model;
- personalized greeting on the home page;
- CSRF protection through Django templates;
- custom CSS styling.
