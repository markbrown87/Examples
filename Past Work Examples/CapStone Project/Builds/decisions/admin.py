from django.contrib import admin
from .models import UserProfile, Decide, Item, Criteria
from django.http import HttpResponse

# Register your models here.
class CriteriaInline(admin.TabularInline):
    model = Criteria

class ItemInline(admin.TabularInline):
    model = Item

class DecideAdmin(admin.ModelAdmin):
    inlines = [
        CriteriaInline,
        ItemInline,
    ]

def export_csv(modeladmin, request, queryset):
	import csv
	from django.utils.encoding import smart_str
	response = HttpResponse(content_type='text/csv')
	response['Content-Disposition'] = 'attachment; filename=mautdecisions.csv'
	writer = csv.writer(response, csv.excel)
	response.write(u'\ufeff'.encode('utf8'))

	for user in queryset:
		#Start off by putting the user's info first
		writer.writerow([
			smart_str(u"USER ID"),
			smart_str(u"Detail name"),
			smart_str(u"Detail info"),
			])
		writer.writerow([
			smart_str(user.pk),
			smart_str(u"City"),
			smart_str(user.city),
			])
		writer.writerow([
			smart_str(user.pk),
			smart_str(u"State"),
			smart_str(user.state)
			])
		writer.writerow([
			smart_str(user.pk),
			smart_str(u"Age"),
			smart_str(user.age)
			])
		writer.writerow([
			smart_str(user.pk),
			smart_str(u"Gender"),
			smart_str(user.gender),
			])
		writer.writerow([
			smart_str(user.pk),
			smart_str(u"Income"),
			smart_str(user.income)
			])
		writer.writerow([
			smart_str(user.pk),
			smart_str(u"Race"),
			smart_str(user.race)
			])
		writer.writerow([
			smart_str(user.pk),
			smart_str(u"Ethnicity"),
			smart_str(user.ethnicity)
			])
		writer.writerow([
			smart_str(u" ")
			])
		writer.writerow([
			smart_str(user.pk),
			smart_str(u"DECISIONS:"),
			])
		for decision in user.decide_set.all():
			writer.writerow([
				smart_str(user.pk),
				smart_str(u"Decision"),
				smart_str(decision.decisionName)
				])
			writer.writerow([
				smart_str(user.pk),
				smart_str(u"CRITERIA"),
				smart_str(u"WEIGHT")
				])
			for criteria in decision.criteria.all():
				writer.writerow([
					smart_str(user.pk),
					smart_str(criteria.criteriaName),
					smart_str(criteria.criteriaWeight),
					])
		writer.writerow([
			smart_str(u""),
			])

	return response
export_csv.short_description = u"Export CSV"

class UserProfileAdmin(admin.ModelAdmin):
	list_display = ('user', 'firstName', 'lastName')
	actions = [export_csv]

admin.site.register(UserProfile, UserProfileAdmin)
admin.site.register(Decide,DecideAdmin)
