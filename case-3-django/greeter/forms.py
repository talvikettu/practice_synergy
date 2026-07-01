from django import forms


class GreetingForm(forms.Form):
    name = forms.CharField(
        max_length=120,
        label="Ваше имя",
        widget=forms.TextInput(
            attrs={
                "class": "name-input",
                "placeholder": "Введите ваше имя",
                "autocomplete": "off",
            }
        ),
        error_messages={
            "required": "Пожалуйста, введите имя.",
            "max_length": "Имя не должно быть длиннее 120 символов.",
        },
    )

    def clean_name(self):
        name = self.cleaned_data["name"].strip()
        if not name:
            raise forms.ValidationError("Пожалуйста, введите имя.")
        return name
