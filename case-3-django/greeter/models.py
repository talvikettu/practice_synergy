from django.db import models


class Visitor(models.Model):
    name = models.CharField(max_length=120, verbose_name="Имя")

    class Meta:
        ordering = ["-id"]
        verbose_name = "Посетитель"
        verbose_name_plural = "Посетители"

    def __str__(self):
        return self.name
