Public Class Form1
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim form As Form2

        form = New Form2
        Form2.MdiParent = Me
        Form2.Show()
    End Sub
End Class
