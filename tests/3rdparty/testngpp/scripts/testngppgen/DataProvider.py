
class DataProvider:
   def __init__(self, name, data_groups):
      self.name = name
      self.data_groups = data_groups

   def set_scope(self, scope):
      pass

   def get_name(self):
      return self.name

   def get_data_groups(self):
      return self.data_groups
