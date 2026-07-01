from django.shortcuts import render

from .forms import GreetingForm
from .models import Visitor


def home(request):
    greeting_name = None
    latest_visitors = Visitor.objects.all()[:5]

    if request.method == "POST":
        form = GreetingForm(request.POST)
        if form.is_valid():
            greeting_name = form.cleaned_data["name"]
            Visitor.objects.create(name=greeting_name)
            latest_visitors = Visitor.objects.all()[:5]
            form = GreetingForm()
    else:
        form = GreetingForm()

    return render(
        request,
        "greeter/home.html",
        {
            "form": form,
            "greeting_name": greeting_name,
            "latest_visitors": latest_visitors,
        },
    )
